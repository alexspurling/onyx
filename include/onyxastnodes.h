#ifndef ONYXASTNODES_H
#define ONYXASTNODES_H

#include "onyxlex.h"
#include "onyxtypes.h"


typedef struct AstNode AstNode;
typedef struct AstTyped AstTyped;

typedef struct AstBinOp AstBinaryOp;
typedef struct AstUnaryOp AstUnaryOp;
typedef struct AstNumLit AstNumLit;
typedef struct AstStrLit AstStrLit;
typedef struct AstLocal AstLocal;
typedef struct AstCall AstCall;
typedef struct AstIntrinsicCall AstIntrinsicCall;
typedef struct AstArgument AstArgument;
typedef struct AstAddressOf AstAddressOf;
typedef struct AstDereference AstDereference;
typedef struct AstArrayAccess AstArrayAccess;
typedef struct AstFieldAccess AstFieldAccess;
typedef struct AstSizeOf AstSizeOf;
typedef struct AstAlignOf AstAlignOf;
typedef struct AstFileContents AstFileContents;
typedef struct AstStructLiteral AstStructLiteral;

typedef struct AstReturn AstReturn;
typedef struct AstBreak AstBreak;
typedef struct AstContinue AstContinue;

typedef struct AstBlock AstBlock;
typedef struct AstIf AstIf;
typedef struct AstFor AstFor;
typedef struct AstWhile AstWhile;
typedef struct AstDefer AstDefer;

typedef struct AstType AstType;
typedef struct AstBasicType AstBasicType;
typedef struct AstPointerType AstPointerType;
typedef struct AstFunctionType AstFunctionType;
typedef struct AstArrayType AstArrayType;
typedef struct AstStructType AstStructType;
typedef struct AstEnumType AstEnumType;
typedef struct AstEnumValue AstEnumValue;
typedef struct AstTypeAlias AstTypeAlias;

typedef struct AstBinding AstBinding;
typedef struct AstMemRes AstMemRes;
typedef struct AstInclude AstInclude;
typedef struct AstUsePackage AstUsePackage;
typedef struct AstAlias AstAlias;
typedef struct AstGlobal AstGlobal;
typedef struct AstFunction AstFunction;
typedef struct AstOverloadedFunction AstOverloadedFunction;

typedef struct AstPackage AstPackage;
typedef struct Package Package;

typedef struct Scope {
    struct Scope *parent;
    bh_table(AstNode *) symbols;
} Scope;

extern Scope* scope_create(bh_allocator a, Scope* parent);


typedef enum AstKind {
    Ast_Kind_Error,
    Ast_Kind_Program,
    Ast_Kind_Package,
    Ast_Kind_Include_File,
    Ast_Kind_Include_Folder,
    Ast_Kind_Use_Package,
    Ast_Kind_Alias,
    Ast_Kind_Memres,

    Ast_Kind_Binding,
    Ast_Kind_Function,
    Ast_Kind_Overloaded_Function,
    Ast_Kind_Block,
    Ast_Kind_Local_Group,
    Ast_Kind_Local,
    Ast_Kind_Global,
    Ast_Kind_Symbol,

    Ast_Kind_Unary_Op,
    Ast_Kind_Binary_Op,

    Ast_Kind_Type_Start,
    Ast_Kind_Type,
    Ast_Kind_Basic_Type,
    Ast_Kind_Pointer_Type,
    Ast_Kind_Function_Type,
    Ast_Kind_Array_Type,
    Ast_Kind_Struct_Type,
    Ast_Kind_Enum_Type,
    Ast_Kind_Type_Alias,
    Ast_Kind_Type_End,

    Ast_Kind_Struct_Member,
    Ast_Kind_Enum_Value,

    Ast_Kind_NumLit,
    Ast_Kind_StrLit,
    Ast_Kind_Param,
    Ast_Kind_Argument,
    Ast_Kind_Call,
    Ast_Kind_Intrinsic_Call,
    Ast_Kind_Return,
    Ast_Kind_Address_Of,
    Ast_Kind_Dereference,
    Ast_Kind_Array_Access,
    Ast_Kind_Field_Access,
    Ast_Kind_Ufc,
    Ast_Kind_Size_Of,
    Ast_Kind_Align_Of,
    Ast_Kind_File_Contents,
    Ast_Kind_Struct_Literal,

    Ast_Kind_If,
    Ast_Kind_For,
    Ast_Kind_While,
    Ast_Kind_Break,
    Ast_Kind_Continue,
    Ast_Kind_Defer,

    Ast_Kind_Count
} AstKind;

// NOTE: Some of these flags will overlap since there are
// only 32-bits of flags to play with
typedef enum AstFlags {
    // Top-level flags
    Ast_Flag_Exported          = BH_BIT(0),
    Ast_Flag_Foreign           = BH_BIT(1),
    Ast_Flag_Const             = BH_BIT(2),
    Ast_Flag_Comptime          = BH_BIT(3),
    Ast_Flag_Private_Package   = BH_BIT(4),

    // Global flags
    Ast_Flag_Global_Stack_Top  = BH_BIT(30),
    Ast_Flag_Global_Stack_Base = BH_BIT(31),

    // Function flags
    Ast_Flag_Inline            = BH_BIT(8),
    Ast_Flag_Intrinsic         = BH_BIT(9),
    Ast_Flag_Function_Used     = BH_BIT(10),
    Ast_Flag_No_Stack          = BH_BIT(11),

    // Expression flags
    Ast_Flag_Expr_Ignored      = BH_BIT(8),
    Ast_Flag_Param_Use         = BH_BIT(10),
    Ast_Flag_Address_Taken     = BH_BIT(11),

    // Type flags
    Ast_Flag_Type_Is_Resolved  = BH_BIT(8),

    // Enum flags
    Ast_Flag_Enum_Is_Flags     = BH_BIT(11),
} AstFlags;

typedef enum UnaryOp {
    Unary_Op_Negate,
    Unary_Op_Not,
    Unary_Op_Cast,
} UnaryOp;

typedef enum BinaryOp {
    Binary_Op_Add             = 0,
    Binary_Op_Minus           = 1,
    Binary_Op_Multiply        = 2,
    Binary_Op_Divide          = 3,
    Binary_Op_Modulus         = 4,

    Binary_Op_Equal           = 5,
    Binary_Op_Not_Equal       = 6,
    Binary_Op_Less            = 7,
    Binary_Op_Less_Equal      = 8,
    Binary_Op_Greater         = 9,
    Binary_Op_Greater_Equal   = 10,

    Binary_Op_And             = 11,
    Binary_Op_Or              = 12,
    Binary_Op_Xor             = 13,
    Binary_Op_Shl             = 14,
    Binary_Op_Shr             = 15,
    Binary_Op_Sar             = 16,

    Binary_Op_Bool_And        = 17,
    Binary_Op_Bool_Or         = 18,

    Binary_Op_Assign_Start    = 19,
    Binary_Op_Assign          = 20,
    Binary_Op_Assign_Add      = 21,
    Binary_Op_Assign_Minus    = 22,
    Binary_Op_Assign_Multiply = 23,
    Binary_Op_Assign_Divide   = 24,
    Binary_Op_Assign_Modulus  = 25,
    Binary_Op_Assign_And      = 26,
    Binary_Op_Assign_Or       = 27,
    Binary_Op_Assign_Xor      = 28,
    Binary_Op_Assign_Shl      = 29,
    Binary_Op_Assign_Shr      = 30,
    Binary_Op_Assign_Sar      = 31,
    Binary_Op_Assign_End      = 32,

    Binary_Op_Pipe            = 33,
} BinaryOp;

typedef enum OnyxIntrinsic {
    ONYX_INTRINSIC_UNDEFINED,

    ONYX_INTRINSIC_MEMORY_SIZE, ONYX_INTRINSIC_MEMORY_GROW,

    ONYX_INTRINSIC_I32_CLZ,   ONYX_INTRINSIC_I32_CTZ, ONYX_INTRINSIC_I32_POPCNT,
    ONYX_INTRINSIC_I32_AND,   ONYX_INTRINSIC_I32_OR,  ONYX_INTRINSIC_I32_XOR,
    ONYX_INTRINSIC_I32_SHL,   ONYX_INTRINSIC_I32_SLR, ONYX_INTRINSIC_I32_SAR,
    ONYX_INTRINSIC_I32_ROTL,  ONYX_INTRINSIC_I32_ROTR,

    ONYX_INTRINSIC_I64_CLZ,   ONYX_INTRINSIC_I64_CTZ, ONYX_INTRINSIC_I64_POPCNT,
    ONYX_INTRINSIC_I64_AND,   ONYX_INTRINSIC_I64_OR,  ONYX_INTRINSIC_I64_XOR,
    ONYX_INTRINSIC_I64_SHL,   ONYX_INTRINSIC_I64_SLR, ONYX_INTRINSIC_I64_SAR,
    ONYX_INTRINSIC_I64_ROTL,  ONYX_INTRINSIC_I64_ROTR,

    ONYX_INTRINSIC_F32_ABS,   ONYX_INTRINSIC_F32_SQRT,
    ONYX_INTRINSIC_F32_CEIL,  ONYX_INTRINSIC_F32_FLOOR,
    ONYX_INTRINSIC_F32_TRUNC, ONYX_INTRINSIC_F32_NEAREST,
    ONYX_INTRINSIC_F32_MIN,   ONYX_INTRINSIC_F32_MAX,
    ONYX_INTRINSIC_F32_COPYSIGN,

    ONYX_INTRINSIC_F64_ABS,   ONYX_INTRINSIC_F64_SQRT,
    ONYX_INTRINSIC_F64_CEIL,  ONYX_INTRINSIC_F64_FLOOR,
    ONYX_INTRINSIC_F64_TRUNC, ONYX_INTRINSIC_F64_NEAREST,
    ONYX_INTRINSIC_F64_MIN,   ONYX_INTRINSIC_F64_MAX,
    ONYX_INTRINSIC_F64_COPYSIGN,
} OnyxIntrinsic;


// Base Nodes
#define AstNode_members {     \
    AstKind kind;             \
    u32 flags;                \
    OnyxToken *token;         \
    AstNode *next;            \
};
#define AstNode_base struct AstNode_members;
struct AstNode AstNode_members;

// NOTE: 'type_node' is filled out by the parser.
// For a type such as '^^i32', the tree would look something like
//
//      Typed Thing -> AstPointerType -> AstPointerType -> AstNode (symbol node)
//
// The symbol node will be filled out during symbol resolution.
// It will end up pointing to an AstBasicType that corresponds to
// the underlying type.
//
// 'type' is filled out afterwards. If it is NULL, the Type* is built
// using the type_node. This can then be used to typecheck this node.
#define AstTyped_members     { \
    AstNode_base;              \
    AstType *type_node;        \
    Type *type;                \
}
#define AstTyped_base struct AstTyped_members;
struct AstTyped AstTyped_members;

// Expression Nodes
struct AstBinOp         { AstTyped_base; BinaryOp operation; AstTyped *left, *right; };
struct AstUnaryOp       { AstTyped_base; UnaryOp operation; AstTyped *expr; };
struct AstNumLit        { AstTyped_base; union { i32 i; i64 l; f32 f; f64 d; } value; };
struct AstStrLit        { AstTyped_base; u64 addr; };
struct AstLocal         { AstTyped_base; AstLocal *prev_local; };
struct AstCall          { AstTyped_base; AstArgument *arguments; u64 arg_count; AstTyped *callee; };
struct AstIntrinsicCall { AstTyped_base; AstArgument *arguments; u64 arg_count; OnyxIntrinsic intrinsic; };
struct AstArgument      { AstTyped_base; AstTyped *value; };
struct AstAddressOf     { AstTyped_base; AstTyped *expr; };
struct AstDereference   { AstTyped_base; AstTyped *expr; };
struct AstArrayAccess   { AstTyped_base; AstTyped *addr; AstTyped *expr; u64 elem_size; };
struct AstFieldAccess   { AstTyped_base; AstTyped *expr; u64 offset; };
struct AstSizeOf        { AstTyped_base; AstType *so_type; u64 size; };
struct AstAlignOf       { AstTyped_base; AstType *ao_type; u64 alignment; };
struct AstFileContents  { AstTyped_base; OnyxToken *filename; };
struct AstStructLiteral { AstTyped_base; AstTyped *stnode; bh_arr(AstTyped *) values; };

// Intruction Node
struct AstReturn        { AstNode_base; AstTyped* expr; };
struct AstBreak         { AstNode_base; u64 count; };
struct AstContinue      { AstNode_base; u64 count; };

// Structure Nodes
struct AstBlock         { AstNode_base; AstNode *body; Scope *scope; bh_arr(AstLocal *) locals; };
struct AstWhile         { AstNode_base; AstTyped *cond; AstBlock *stmt; };
struct AstDefer         { AstNode_base; AstNode *stmt; };
struct AstFor           {
    AstNode_base;

    // NOTE: Stores the iteration variable
    Scope *scope;

    // NOTE: Local defining the iteration variable
    AstLocal* var;

    AstTyped *start, *end, *step;

    AstBlock *stmt;
};
struct AstIf {
    AstNode_base;
    AstTyped *cond;

    AstBlock *true_stmt;
    AstBlock *false_stmt;
};

// Type Nodes
// NOTE: This node is very similar to an AstNode, just
// without the 'next' member. This is because types
// can't be in expressions so a 'next' thing
// doesn't make sense.
#define AstType_members { AstKind kind; u32 flags; OnyxToken* token; char* name; }
#define AstType_base struct AstType_members;
struct AstType AstType_members;

struct AstBasicType     { AstType_base; Type* type; };
struct AstPointerType   { AstType_base; AstType* elem; };
struct AstFunctionType  { AstType_base; AstType* return_type; u64 param_count; AstType* params[]; };
struct AstArrayType     { AstType_base; AstType* elem; AstTyped *count_expr; };
struct AstStructType {
    AstType_base;

    bh_arr(AstTyped *) members;

    // NOTE: Used to cache the actual type, since building
    // a struct type is kind of complicated and should
    // only happen once.
    Type *stcache;
};
struct AstEnumType {
    AstType_base;
    Scope *scope;

    AstType *backing;
    Type    *backing_type;

    bh_arr(AstEnumValue *) values;

    // NOTE: Used to cache the actual type for the same reason as above.
    Type *etcache;
};
struct AstEnumValue { AstTyped_base; AstNumLit* value; };
struct AstTypeAlias { AstType_base; AstType* to; };

// Top level nodes
struct AstBinding       { AstTyped_base; AstNode* node; };
struct AstMemRes        { AstTyped_base; u64 addr; AstTyped *initial_value; };
struct AstInclude       { AstNode_base; OnyxToken *name; };
struct AstUsePackage    {
    AstNode_base;

    AstPackage *package;
    OnyxToken *alias;
    bh_arr(AstAlias *) only;
};
struct AstAlias         {
    AstNode_base;
    OnyxToken *alias;
};
struct AstGlobal        {
    AstTyped_base;

    union {
        // NOTE: Used when a global is exported with a specific name
        OnyxToken* exported_name;

        // NOTE: Used when the global is declared as foreign
        struct {
            OnyxToken* foreign_module;
            OnyxToken* foreign_name;
        };
    };
};
struct AstFunction      {
    AstTyped_base;

    Scope *scope;
    AstBlock *body;
    AstLocal *params;
    bh_arr(AstLocal *) locals;

    union {
        // NOTE: Used when a function is exported with a specific name
        OnyxToken* exported_name;
        OnyxToken* intrinsic_name;

        // NOTE: Used when the function is declared as foreign
        struct {
            OnyxToken* foreign_module;
            OnyxToken* foreign_name;
        };
    };
};
struct AstOverloadedFunction {
    AstTyped_base;

    bh_arr(AstTyped *) overloads;
};
struct AstPackage {
    AstNode_base;

    Package* package;
};

// NOTE: An Entity represents something will need to be
// processed later down the pipeline.
typedef enum EntityType {
    Entity_Type_Unknown,
    Entity_Type_Use_Package,
    Entity_Type_String_Literal,
    Entity_Type_File_Contents,
    Entity_Type_Enum,
    Entity_Type_Type_Alias,
    Entity_Type_Memory_Reservation,
    Entity_Type_Function_Header,
    Entity_Type_Global_Header,
    Entity_Type_Expression,
    Entity_Type_Global,
    Entity_Type_Overloaded_Function,
    Entity_Type_Function,
} EntityType;

typedef struct Entity {
    EntityType type;
    Package *package;

    union {
        AstUsePackage         *use_package;
        AstFunction           *function;
        AstOverloadedFunction *overloaded_function;
        AstGlobal             *global;
        AstTyped              *expr;
        AstStrLit             *strlit;
        AstFileContents       *file_contents;
        AstType               *type_alias;
        AstEnumType           *enum_type;
        AstMemRes             *mem_res;
    };
} Entity;

struct Package {
    char *name;

    Scope *scope;
    Scope *include_scope;
    Scope *private_scope;
};

// NOTE: Simple data structure for storing what comes out of the parser
typedef struct ProgramInfo {
    Scope *global_scope;

    bh_table(Package *)   packages;
    bh_arr(Entity)        entities;

    u32 foreign_func_count;
    u32 foreign_global_count;
} ProgramInfo;



// NOTE: Basic internal types constructed in the parser
extern AstBasicType basic_type_void;
extern AstBasicType basic_type_bool;
extern AstBasicType basic_type_i8;
extern AstBasicType basic_type_u8;
extern AstBasicType basic_type_i16;
extern AstBasicType basic_type_u16;
extern AstBasicType basic_type_i32;
extern AstBasicType basic_type_u32;
extern AstBasicType basic_type_i64;
extern AstBasicType basic_type_u64;
extern AstBasicType basic_type_f32;
extern AstBasicType basic_type_f64;
extern AstBasicType basic_type_rawptr;

extern AstNumLit builtin_heap_start;
extern AstGlobal builtin_stack_top;

typedef struct BuiltinSymbol {
    char*    package;
    char*    sym;
    AstNode* node;
} BuiltinSymbol;

extern const BuiltinSymbol builtin_symbols[];

void initialize_builtins();


// NOTE: Useful not inlined functions
AstTyped* ast_reduce(bh_allocator a, AstTyped* node);
void promote_numlit_to_larger(AstNumLit* num);

// NOTE: Useful inlined functions
static inline b32 is_lval(AstNode* node) {
    return (node->kind == Ast_Kind_Local)
        || (node->kind == Ast_Kind_Global)
        || (node->kind == Ast_Kind_Dereference)
        || (node->kind == Ast_Kind_Array_Access)
        || (node->kind == Ast_Kind_Field_Access)
        || (node->kind == Ast_Kind_Memres);
}

static inline b32 binop_is_assignment(AstBinaryOp* binop) {
    return (binop->operation >= Binary_Op_Assign_Start
            && binop->operation <= Binary_Op_Assign_End);
}

static inline b32 binop_is_compare(AstBinaryOp* binop) {
    return (binop->operation >= Binary_Op_Equal
            && binop->operation <= Binary_Op_Greater_Equal);
}

static inline b32 node_is_type(AstNode* node) {
    return (node->kind > Ast_Kind_Type_Start) && (node->kind < Ast_Kind_Type_End);
}

#endif // #ifndef ONYXASTNODES_H
