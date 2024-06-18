#include "AddToSub.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Metadata.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/IRBuilder.h"

using namespace llvm;

namespace addtosub {
    PreservedAnalyses AddToSubPass::run(Function &F, FunctionAnalysisManager &FAM) {
        auto &AddInsts = FAM.getResult<AddToSubAnalysis>(F);
        for (auto *AI: AddInsts) {
            IRBuilder<> builder(AI);
            Value *sub = builder.CreateSub(AI->getOperand(0), AI->getOperand(1), AI->getName());
            AI->replaceAllUsesWith(sub);
            AI->eraseFromParent();
        }

        return PreservedAnalyses::all();
    }
}