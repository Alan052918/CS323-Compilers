#ifndef ENUMS_H
#define ENUMS_H

/**
 * Exp types
 */
enum ExpType {
  ComplexExp,
  CharExp,
  FloatingPointExp,
  IdExp,
  IntegerExp,
  KeywordExp
};

/**
 * Symbol table search modes
 * - Decf: for declaration/definition, look for id in current scope only
 * - Use: for usage, look for id recursively in the scope hierarchy
 */
enum SearchMode { DecfMode, UseMode };

/**
 * Type definition categories
 */
enum Category { PRIMITIVE, ARRAY, STRUCTURE };
enum Primitive { INTEGER, FLOATING_POINT, CHARACTER };

/**
 * Syntax tree node types
 */
enum NodeType { Int, Float, Char, Type, Id, Keyword, Nonterminal };

#endif  // ENUMS_H
