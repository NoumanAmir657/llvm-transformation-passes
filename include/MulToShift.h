#ifndef MUL_TO_SHIFT_H
#define MUL_TO_SHIFT_H

#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Instructions.h"

namespace multoshift {
    struct MulToShiftAnalysis : public llvm::AnalysisInfoMixin<MulToShiftAnalysis> {
        using Result = llvm::SmallVector<llvm::BinaryOperator *, 0>;
        Result run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM);
        static llvm::AnalysisKey Key;
    };

    struct MulToShiftPrinterPass : public llvm::PassInfoMixin<MulToShiftPrinterPass> {
        explicit MulToShiftPrinterPass(llvm::raw_ostream &OS) : OS(OS) {}
        llvm::PreservedAnalyses run(llvm::Function &F,
                                    llvm::FunctionAnalysisManager &FAM);

    private:
        llvm::raw_ostream &OS;
    };

    struct MulToShiftPass : public llvm::PassInfoMixin<MulToShiftPass> {
        llvm::PreservedAnalyses run(llvm::Function &F,
                                    llvm::FunctionAnalysisManager &FAM);
    };
}

#endif