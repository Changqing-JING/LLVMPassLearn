#include "AddConst.h"
using namespace llvm;

namespace addconst {

void ReplaceAddInstWithConstant(BinaryOperator *BO) {
  ConstantInt *first = cast<ConstantInt>(BO->getOperand(0));
  ConstantInt *second = cast<ConstantInt>(BO->getOperand(1));

  auto sum = ConstantExpr::getAdd(first, second);
  BO->replaceAllUsesWith(sum);
  BO->eraseFromParent();
}

PreservedAnalyses AddConstPass::run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM) {
  AddConstAnalysis::Result const &AddInsts = FAM.getResult<AddConstAnalysis>(F);

  for (BinaryOperator *BO : AddInsts) {
    ReplaceAddInstWithConstant(BO);
  }

  PreservedAnalyses PA = PreservedAnalyses::all();

  PA.abandon<AddConstAnalysis>();

  return PA;
}
} // namespace addconst