#include "AddConst.h"

using namespace llvm;

namespace addconst {
AnalysisKey AddConstAnalysis::Key;

bool isConstantIntOnly(Instruction const &I) {
  for (Use const &Op : I.operands()) {
    if (!isa<ConstantInt>(Op)) {
      return false;
    }
  }
  return true;
}

AddConstAnalysis::Result AddConstAnalysis::run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM) {
  SmallVector<BinaryOperator *, 0> AddInstructions;
  for (BasicBlock &BB : F) {
    for (Instruction &I : BB) {
      if (I.isBinaryOp() && (I.getOpcode() == Instruction::BinaryOps::Add) && isConstantIntOnly(I)) {
        AddInstructions.push_back(&cast<BinaryOperator>(I));
      }
    }
  }
  return AddInstructions;
}

PreservedAnalyses AddConstPrinterPass::run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM) {

  AddConstAnalysis::Result const &AddInsts = FAM.getResult<AddConstAnalysis>(F);
  OS << F.getName() << "\n";

  for (BinaryOperator const *Add : AddInsts) {
    OS << *Add << "\n";
  }

  return PreservedAnalyses::all();
}

} // namespace addconst