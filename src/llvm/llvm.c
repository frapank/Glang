#include "llvm.h"

#include <llvm-c/Analysis.h>
#include <llvm-c/Target.h>
#include <llvm-c/TargetMachine.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "llvm_generator.h"

void llvm_generate(struct function_list function_list, const char* output_file)
{
    // Find main function
    LLVMContextRef context = LLVMContextCreate();
    const LLVMModuleRef module = LLVMModuleCreateWithName("module");
    struct function* main_fun = ast_get_function_by_name("main", function_list);
    if (main_fun == NULL) {
        fprintf(stderr, "[-] Main entry point don't exist \n");
        exit(1);
    }

    // Print for debug
    llvm_generator_function_ir(main_fun, &module);
    #ifdef DEBUG
    char* ir = LLVMPrintModuleToString(module);
    printf("\n[debug] Generated LLVM IR:\n");
    printf("%s\n", ir);
    LLVMDisposeMessage(ir);
    #endif

    // Module validation
    char* verify_error = NULL;
    if (LLVMVerifyModule(module, LLVMAbortProcessAction, &verify_error)) {
        fprintf(stderr, "[-] Module verification failed: %s\n", verify_error);
        LLVMDisposeMessage(verify_error);
        exit(1);
    }

    LLVMInitializeNativeTarget();
    LLVMInitializeNativeAsmPrinter();
    LLVMInitializeNativeAsmParser();

    // Configure the target machine
    char* triple = LLVMGetDefaultTargetTriple();
    LLVMTargetRef target;
    char* error = NULL;

    if (LLVMGetTargetFromTriple(triple, &target, &error)) {
        fprintf(stderr, "[-] Failed to get target: %s\n", error);
        LLVMDisposeMessage(error);
        LLVMDisposeMessage(triple);
        exit(1);
    }

    const LLVMTargetMachineRef target_machine =
        LLVMCreateTargetMachine(target, triple, "", "", LLVMCodeGenLevelDefault,
                                LLVMRelocDefault, LLVMCodeModelDefault);
    LLVMDisposeMessage(triple);

    // Create object file
    if (LLVMTargetMachineEmitToFile(target_machine, module, "output.o",
                                    LLVMObjectFile, &error)) {
        fprintf(stderr, "[-] Failed to emit object file: %s\n", error);
        LLVMDisposeMessage(error);
        exit(1);
    }

    // Link the object file
    char link_command[1024];
    snprintf(link_command, sizeof(link_command), "clang output.o -o %s",
             output_file);

    printf("[+] Linking to create executable...\n");
    const int link_result = system(link_command);
    if (link_result != 0) {
        fprintf(stderr, "[-] Linking failed\n");
        exit(1);
    }

    printf("[+] Executable '%s' created successfully!\n", output_file);

    // Cleanup
    LLVMDisposeModule(module);
    LLVMContextDispose(context);
}
