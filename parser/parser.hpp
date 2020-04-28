#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
#include <stack>
#include <map>

// #include "../lexer/lexer.hpp"
#include "../poliz/poliz.hpp"

using namespace execution;

class Parser{
 public:
	explicit Parser(std::istream& input);
	Operations operations;
	void Run(Context& context);

 private:
 	
	Lexer lexer_;
	std::stack<int> indents;
	std::stack<ValueType> operand_types;
	std::stack<const execution::OperationIndex> loop_starts;
	std::stack<const execution::OperationIndex> breaks;
	std::unordered_map<VariableName, ValueType> var_types;

	std::string TypeToString(Lexeme::LexemeType type) const;

	void PostOp(std::stack<ValueType> &operand_types, ValueType op1, ValueType op2 = Int);

	void ProcessUnaryTypeExceptions(ValueType op1, Lexeme::LexemeType type);
	void ProcessBinaryTypeExceptions(ValueType op1, ValueType op2, Lexeme::LexemeType type);

	int IndentCounter();

	int Block(Context& context);

	// For
	int ForBlock(Context& context);
	void Range(Context& context);
	void Interval(Context& context);

	// If
	int IfBlock(Context& context);
	int ElseBlock(Context& context);

	// While
	int WhileBlock(Context& context);
	
	int InnerBlock(Context& context);

	void Print(Context& context);

	void Assign(Context& context);

	void Expression(Context& context);
	void OrParts(Context& context);
	void AndParts(Context& context);
	void LogicalParts(Context& context);
	void CompParts(Context& context);
	void SumParts(Context& context);
	void MultParts(Context& context);
	void Cast(Context& context);
	void Members(Context& context);
};