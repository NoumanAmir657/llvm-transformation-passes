#include "MulToShift.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Metadata.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/IRBuilder.h"

using namespace llvm;

namespace multoshift {
    PreservedAnalyses MulToShiftPass::run(Function &F, FunctionAnalysisManager &FAM) {
        bool flag = true;
        auto &MulInsts = FAM.getResult<MulToShiftAnalysis>(F);
        for (auto *MI: MulInsts) {
            if (auto *C = dyn_cast<ConstantInt>(MI->getOperand(1))) {
                if (C->getValue().isPowerOf2()) {
                    IRBuilder<> Builder(MI);
                    Value *ShiftAmount = Builder.getInt32(C->getValue().exactLogBase2());
                    Value *ShlInst = Builder.CreateShl(MI->getOperand(0), ShiftAmount);
                    MI->replaceAllUsesWith(ShlInst);
                    MI->eraseFromParent(); // Remove the multiplication instruction
                    flag = true;
                }
            }
        }
        return flag ? PreservedAnalyses::none() : PreservedAnalyses::all();
    }
}