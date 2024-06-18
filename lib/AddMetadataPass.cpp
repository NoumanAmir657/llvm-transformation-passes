#include "AddMetadata.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Metadata.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/IRBuilder.h"

using namespace llvm;

namespace addmetadata {
    PreservedAnalyses AddMetadataPass::run(Function &F, FunctionAnalysisManager &FAM) {
        auto &LoadInsts = FAM.getResult<AddMetadataAnalysis>(F);

        for (auto *LI: LoadInsts) {
            LLVMContext &Context = LI->getContext();
            MDNode *Node = MDNode::get(Context, MDString::get(Context, ""));
            LI->setMetadata("x10", Node);
        }
        return PreservedAnalyses::all();
    }
}