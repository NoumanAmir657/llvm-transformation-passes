#include "AddCall.h"
#include "llvm/IR/Constants.h"
#include "llvm/Support/Casting.h"
#include "llvm/IR/Instructions.h"
#include <iostream>

using namespace llvm;

namespace addcall {

    AnalysisKey AddCallAnalysis::Key;

    AddCallAnalysis::Result AddCallAnalysis::run(Function &F,
                                                FunctionAnalysisManager &FAM) {
        SmallVector<CallInst *, 0> CallInsts;
        for (BasicBlock &BB : F) {
            for (Instruction &I : BB) {
                if (auto *callInst = dyn_cast<CallInst>(&I)){
                    Function *callee = callInst->getCalledFunction();
                    if (callee && callee->getName() == "printf") {
                        CallInsts.push_back(callInst);
                    }
                }
            }
        }
        return CallInsts;
    }

    PreservedAnalyses AddCallPrinterPass::run(Function &F,
                                            FunctionAnalysisManager &FAM) {
        auto &CallInsts = FAM.getResult<AddCallAnalysis>(F);
        OS << "=============================================\n";
        OS << "|| " << F.getName() << " ||\n";
        OS << "=============================================\n";
        for (auto &Call : CallInsts) OS << *Call << "\n";
        OS << "=============================================\n";
        return PreservedAnalyses::all();
    }
}