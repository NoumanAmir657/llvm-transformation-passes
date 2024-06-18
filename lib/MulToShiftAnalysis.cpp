#include "MulToShift.h"
#include "llvm/IR/Constants.h"
#include "llvm/Support/Casting.h"
#include "llvm/IR/Instructions.h"

using namespace llvm;

namespace multoshift {

    AnalysisKey MulToShiftAnalysis::Key;

    MulToShiftAnalysis::Result MulToShiftAnalysis::run(Function &F,
                                                FunctionAnalysisManager &FAM) {

        SmallVector<BinaryOperator *, 0> MulInsts;
        for (BasicBlock &BB : F) {
            for (Instruction &I : BB) {
                if (auto *mulInst = dyn_cast<BinaryOperator>(&I)){
                    if (mulInst->getOpcode() == Instruction::Mul) {
                        MulInsts.push_back(mulInst);
                    }
                }
            }
        }
        return MulInsts;
    }

    PreservedAnalyses MulToShiftPrinterPass::run(Function &F,
                                            FunctionAnalysisManager &FAM) {
        auto &MulInsts = FAM.getResult<MulToShiftAnalysis>(F);
        OS << "=============================================\n";
        OS << "|| " << F.getName() << " ||\n";
        OS << "=============================================\n";
        for (auto &Mul : MulInsts) OS << *Mul << "\n";
        OS << "=============================================\n";
        return PreservedAnalyses::all();
    }
}