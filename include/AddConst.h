#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/PassManager.h>
#include <llvm/Support/raw_ostream.h>

namespace addconst {
struct AddConstAnalysis : public llvm::AnalysisInfoMixin<AddConstAnalysis> {
  using Result = llvm::SmallVector<llvm::BinaryOperator *, 0>;
  Result run(llvm::Function &, llvm::FunctionAnalysisManager &);
  static llvm::AnalysisKey Key;
};

struct AddConstPrinterPass : public llvm::PassInfoMixin<AddConstPrinterPass> {
  explicit AddConstPrinterPass(llvm::raw_ostream &OS_) : OS(OS_) {
  }
  llvm::PreservedAnalyses run(llvm::Function &, llvm::FunctionAnalysisManager &);

private:
  llvm::raw_ostream &OS;
};

} // namespace addconst