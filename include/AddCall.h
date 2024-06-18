#ifndef ADD_CALL_H
#define ADD_CALL_H

#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Instructions.h"

namespace addcall {
    struct AddCallAnalysis : public llvm::AnalysisInfoMixin<AddCallAnalysis> {
        using Result = llvm::SmallVector<llvm::CallInst *, 0>;
        Result run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM);
        static llvm::AnalysisKey Key;
    };

    struct AddCallPrinterPass : public llvm::PassInfoMixin<AddCallPrinterPass> {
        explicit AddCallPrinterPass(llvm::raw_ostream &OS) : OS(OS) {}
        llvm::PreservedAnalyses run(llvm::Function &F,
                                    llvm::FunctionAnalysisManager &FAM);

    private:
        llvm::raw_ostream &OS;
    };

    struct AddCallPass : public llvm::PassInfoMixin<AddCallPass> {
        llvm::PreservedAnalyses run(llvm::Function &F,
                                    llvm::FunctionAnalysisManager &FAM);
    };
}

#endif