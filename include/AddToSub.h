#ifndef ADD_TO_SUB_H
#define ADD_TO_SUB_H

#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Instructions.h"

namespace addtosub {
    struct AddToSubAnalysis : public llvm::AnalysisInfoMixin<AddToSubAnalysis> {
        using Result = llvm::SmallVector<llvm::BinaryOperator *, 0>;
        Result run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM);
        static llvm::AnalysisKey Key;
    };

    struct AddToSubPrinterPass : public llvm::PassInfoMixin<AddToSubPrinterPass> {
        explicit AddToSubPrinterPass(llvm::raw_ostream &OS) : OS(OS) {}
        llvm::PreservedAnalyses run(llvm::Function &F,
                                    llvm::FunctionAnalysisManager &FAM);

    private:
        llvm::raw_ostream &OS;
    };

    struct AddToSubPass : public llvm::PassInfoMixin<AddToSubPass> {
        llvm::PreservedAnalyses run(llvm::Function &F,
                                    llvm::FunctionAnalysisManager &FAM);
    };
}

#endif