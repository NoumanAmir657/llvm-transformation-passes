#include "AddToSub.h"
#include "llvm/IR/Constants.h"
#include "llvm/Support/Casting.h"
#include "llvm/IR/Instructions.h"

using namespace llvm;

namespace addtosub {

    AnalysisKey AddToSubAnalysis::Key;

    AddToSubAnalysis::Result AddToSubAnalysis::run(Function &F,
                                                FunctionAnalysisManager &FAM) {

        SmallVector<BinaryOperator *, 0> AddInsts;
        for (BasicBlock &BB : F) {
            for (Instruction &I : BB) {
                if (auto *addInst = dyn_cast<BinaryOperator>(&I)){
                    if (addInst->getOpcode() == Instruction::Add) {
                        AddInsts.push_back(addInst);
                    }
                }
            }
        }
        return AddInsts;
    }

    PreservedAnalyses AddToSubPrinterPass::run(Function &F,
                                            FunctionAnalysisManager &FAM) {
        auto &AddInsts = FAM.getResult<AddToSubAnalysis>(F);
        OS << "=============================================\n";
        OS << "|| " << F.getName() << " ||\n";
        OS << "=============================================\n";
        for (auto &Add : AddInsts) OS << *Add << "\n";
        OS << "=============================================\n";
        return PreservedAnalyses::all();
    }
}