//===-- AddConst.h ----------------------------------------------*- C++ -*-===//
// Copyright (C) 2020  Luigi D. C. Soares, Augusto Dias Noronha
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the analysis used to collect all add
/// instructions within a function.
///
//===----------------------------------------------------------------------===//

#ifndef ADD_METADATA_H
#define ADD_METADATA_H

#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Instructions.h"

namespace addmetadata {
    struct AddMetadataAnalysis : public llvm::AnalysisInfoMixin<AddMetadataAnalysis> {
        using Result = llvm::SmallVector<llvm::LoadInst *, 0>;
        Result run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM);
        static llvm::AnalysisKey Key;
    };

    struct AddMetadataPrinterPass : public llvm::PassInfoMixin<AddMetadataPrinterPass> {
        explicit AddMetadataPrinterPass(llvm::raw_ostream &OS) : OS(OS) {}
        llvm::PreservedAnalyses run(llvm::Function &F,
                                    llvm::FunctionAnalysisManager &FAM);

    private:
        llvm::raw_ostream &OS;
    };

    struct AddMetadataPass : public llvm::PassInfoMixin<AddMetadataPass> {
        llvm::PreservedAnalyses run(llvm::Function &F,
                                    llvm::FunctionAnalysisManager &FAM);
    };
}

#endif