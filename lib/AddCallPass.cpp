#include "AddCall.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Metadata.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/IRBuilder.h"

using namespace llvm;

namespace addcall {
    PreservedAnalyses AddCallPass::run(Function &F, FunctionAnalysisManager &FAM) {
        auto &CallInsts = FAM.getResult<AddCallAnalysis>(F);
        for (auto *CI: CallInsts) {
                LLVMContext &Ctx = F.getContext();
                Module *M = F.getParent();

                Function *instrumentFunc = M->getFunction("__instrument_printf");
                if (!instrumentFunc) {
                    FunctionType *FTy = FunctionType::get(Type::getVoidTy(Ctx), false);
                    instrumentFunc = Function::Create(FTy, GlobalValue::LinkageTypes::ExternalLinkage, "__instrument_printf", M);
                }
                CallInst::Create(instrumentFunc, "", CI);
        }

        for (BasicBlock &BB : F) {
            for (Instruction &I : BB) {
                if (dyn_cast<ReturnInst>(&I)){
                    LLVMContext &Ctx = F.getContext();
                    Module *M = F.getParent();

                    Function *displayFunc = M->getFunction("__display_printfnum");
                    if (!displayFunc) {
                        FunctionType *FTy = FunctionType::get(Type::getVoidTy(Ctx), false);
                        displayFunc = Function::Create(FTy, GlobalValue::LinkageTypes::ExternalLinkage, "__display_printfnum", M);
                    }
                    CallInst::Create(displayFunc, "", &I);
                }
            }
        }

        return PreservedAnalyses::all();
    }
}