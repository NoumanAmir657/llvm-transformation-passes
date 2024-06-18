#include "AddMetadata.h"
#include "llvm/IR/Constants.h"
#include "llvm/Support/Casting.h"
#include "llvm/IR/Instructions.h"

using namespace llvm;

namespace addmetadata {

    AnalysisKey AddMetadataAnalysis::Key;

    AddMetadataAnalysis::Result AddMetadataAnalysis::run(Function &F,
                                                FunctionAnalysisManager &FAM) {
        SmallVector<LoadInst *, 0> LoadInsts;
        for (BasicBlock &BB : F) {
            for (Instruction &I : BB) {
                if (auto *loadInst = dyn_cast<LoadInst>(&I)){
                    LoadInsts.push_back(loadInst);
                }
            }
        }
        return LoadInsts;
    }

    PreservedAnalyses AddMetadataPrinterPass::run(Function &F,
                                            FunctionAnalysisManager &FAM) {
        auto &LoadInsts = FAM.getResult<AddMetadataAnalysis>(F);
        OS << "=============================================\n";
        OS << "|| " << F.getName() << " ||\n";
        OS << "=============================================\n";
        for (auto &Load : LoadInsts) OS << *Load << "\n";
        OS << "=============================================\n";
        return PreservedAnalyses::all();
    }
}