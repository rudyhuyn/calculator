// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#include "pch.h"


# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "BisonParser.tab.hpp"

// User implementation prologue.


#include "../BisonParserParam.h"

using namespace std;
using namespace CalculationManager;

#pragma warning (disable: 4702)
#pragma warning (disable: 4127)
#pragma warning (disable: 4065)




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif



// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {


  /// Build a parser object.
  Parser::Parser (BisonParserParam * params_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      params (params_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  Parser::syntax_error::syntax_error (const std::string& m)
    : std::runtime_error (m)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
  {
    value = other.value;
  }


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v)
    : Base (t)
    , value (v)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  Parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
  }

  // by_type.
  inline
  Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  Parser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s)
  {
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    return *this;
  }


  template <typename Base>
  inline
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " (";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, params));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;


      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:

    {
                (*params->callback)((yystack_[0].value.keys)->begin);
            }

    break;

  case 3:

    {
                    (yylhs.value.keys) = (yystack_[0].value.keys);
            }

    break;

  case 4:

    {
                    auto equ = new KeyChained(Command::CommandEQU, nullptr);
                    (yylhs.value.keys) = (yystack_[1].value.keys);
                    (yylhs.value.keys)->last->next = equ;
                    (yylhs.value.keys)->last = equ;
            }

    break;

  case 5:

    {
            (yylhs.value.key) = new KeyChained(Command::CommandSIN, nullptr);
        }

    break;

  case 6:

    {
            (yylhs.value.key) = new KeyChained(Command::CommandCOS, nullptr);
        }

    break;

  case 7:

    {
            (yylhs.value.key) = new KeyChained(Command::CommandTAN, nullptr);
        }

    break;

  case 8:

    {
            (yylhs.value.key) = new KeyChained(Command::CommandLOG, nullptr);
        }

    break;

  case 9:

    {
            (yylhs.value.key) = new KeyChained(Command::CommandLOG, nullptr);
        }

    break;

  case 10:

    {
        (yylhs.value.key) = new KeyChained(Command::CommandADD, nullptr);
    }

    break;

  case 11:

    {
        (yylhs.value.key) = new KeyChained(Command::CommandSUB, nullptr);
    }

    break;

  case 12:

    {
        (yylhs.value.key) = new KeyChained(Command::CommandMUL, nullptr);
    }

    break;

  case 13:

    {
        (yylhs.value.key) = new KeyChained(Command::CommandDIV, nullptr);
    }

    break;

  case 14:

    {
        (yylhs.value.key) = new KeyChained(Command::CommandPWR, nullptr);        
    }

    break;

  case 15:

    {
        (yylhs.value.key) = new KeyChained(Command::CommandAnd, nullptr);        
    }

    break;

  case 16:

    {
        (yylhs.value.key) = new KeyChained(Command::CommandOR, nullptr);        
    }

    break;

  case 17:

    {
        (yylhs.value.key) = new KeyChained(Command::CommandXor, nullptr);        
    }

    break;

  case 18:

    {
        (yylhs.value.key) = new KeyChained(Command::CommandNand, nullptr);        
    }

    break;

  case 19:

    {
        (yylhs.value.key) = new KeyChained(Command::CommandNor, nullptr);        
    }

    break;

  case 20:

    {
        (yylhs.value.key) = new KeyChained(Command::CommandLSHF, nullptr);        
    }

    break;

  case 21:

    {
        (yylhs.value.key) = new KeyChained(Command::CommandRSHF, nullptr);        
    }

    break;

  case 22:

    {
        (yylhs.value.key) = new KeyChained(Command::CommandMOD, nullptr);        
    }

    break;

  case 23:

    {
        (yylhs.value.key) = new KeyChained(Command::CommandSIGN, nullptr);
    }

    break;

  case 24:

    {
        (yylhs.value.key) = new KeyChained(Command::CommandNot, nullptr);
    }

    break;

  case 25:

    {
        (yylhs.value.key) = new KeyChained(Command::CommandSQRT, nullptr);
    }

    break;

  case 26:

    {
        (yylhs.value.key) = new KeyChained(Command::CommandSQR, nullptr);
    }

    break;

  case 27:

    {
        (yylhs.value.key) = new KeyChained(Command::CommandCUB, nullptr);
    }

    break;

  case 28:

    { 
                    (yylhs.value.keys) = (yystack_[0].value.keys);
                }

    break;

  case 29:

    { 
                    (yylhs.value.keys)->begin = (yystack_[2].value.keys)->begin;
                    (yystack_[2].value.keys)->last->next = (yystack_[1].value.key);
                    (yystack_[1].value.key)->next = (yystack_[0].value.keys)->begin;
                    (yylhs.value.keys)->last = (yystack_[0].value.keys)->last;
                }

    break;

  case 30:

    {
                (yylhs.value.keys) = (yystack_[0].value.keys);
            }

    break;

  case 31:

    {
                (yylhs.value.keys) = (yystack_[0].value.keys);
            }

    break;

  case 32:

    {
                    (yylhs.value.keys) = (yystack_[0].value.keys);
                    (yylhs.value.keys)->last->next = (yystack_[1].value.key);
                    (yylhs.value.keys)->last = (yystack_[1].value.key);
                }

    break;

  case 33:

    {
                (yylhs.value.keys) = (yystack_[0].value.keys);

            }

    break;

  case 34:

    {
                    (yylhs.value.keys) = (yystack_[1].value.keys);
                    (yylhs.value.keys)->last->next = (yystack_[0].value.key);
                    (yylhs.value.keys)->last = (yystack_[0].value.key);
                }

    break;

  case 35:

    {
                    (yylhs.value.keys) = (yystack_[0].value.keys);
                }

    break;

  case 36:

    {
                    (yystack_[1].value.keys)->begin = new KeyChained(Command::CommandOPENP, (yystack_[1].value.keys)->begin);
                    (yylhs.value.keys) = (yystack_[1].value.keys);
                    (yystack_[1].value.keys)->last->next = new KeyChained(Command::CommandCLOSEP, (yystack_[3].value.key));
                    (yylhs.value.keys)->last = (yystack_[3].value.key);
                }

    break;

  case 37:

    {
            (yylhs.value.keys) = (yystack_[0].value.keys);
    }

    break;

  case 38:

    {
      auto chained = new KeyChainedIterator();
        chained->begin = new KeyChained(Command::CommandPI, nullptr);
      chained->last = chained->begin;
        (yylhs.value.keys) = chained;
    }

    break;

  case 39:

    {
      auto chained = new KeyChainedIterator();
        chained->begin = new KeyChained(Command::CommandEuler, nullptr);
      chained->last = chained->begin;
        (yylhs.value.keys) = chained;
    }

    break;

  case 40:

    {
                    auto close_parenthesis = new KeyChained(Command::CommandCLOSEP, nullptr);

                    (yystack_[1].value.keys)->begin = new KeyChained(Command::CommandOPENP, (yystack_[1].value.keys)->begin);
                    (yylhs.value.keys) = (yystack_[1].value.keys);
                    (yystack_[1].value.keys)->last->next = close_parenthesis;
                    (yylhs.value.keys)->last = close_parenthesis;
                }

    break;



            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yysyntax_error_ (yystack_[0].state, yyla));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }


      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
  }


  const signed char Parser::yypact_ninf_ = -15;

  const signed char Parser::yytable_ninf_ = -1;

  const signed char
  Parser::yypact_[] =
  {
       9,   -15,   -15,     9,   -15,   -15,   -15,   -15,   -15,   -15,
     -15,   -15,   -15,    15,   -15,     0,    24,   -14,    -2,   -15,
     -15,   -12,   -15,     1,   -15,     9,   -15,   -15,   -15,   -15,
     -15,   -15,   -15,   -15,   -15,   -15,   -15,   -15,   -15,   -15,
     -15,     9,   -15,   -15,   -15,   -15,     2,   -15,   -15
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,    23,    24,     0,     5,     6,     7,     8,     9,    25,
      38,    39,    37,     0,     2,     0,     0,     3,    28,    30,
      31,    33,    35,     0,     1,     0,    32,     4,    16,    19,
      17,    15,    18,    20,    21,    10,    11,    12,    13,    22,
      14,     0,    26,    27,    34,    40,     0,    29,    36
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -15,   -15,   -15,   -15,   -15,   -15,   -15,    -3,   -15,   -15,
       7,   -15,   -15
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    41,    16,    44,    17,    18,    19,
      20,    21,    22
  };

  const unsigned char
  Parser::yytable_[] =
  {
      23,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    42,    43,    24,    25,    27,    45,    48,
       1,    40,    46,    26,     2,     3,     0,     4,     5,     6,
       7,     8,     0,     9,     0,     0,    10,    11,    47,    12,
       3,     0,     4,     5,     6,     7,     8,     0,     0,     0,
       0,    10,    11,     0,    12
  };

  const signed char
  Parser::yycheck_[] =
  {
       3,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    25,    26,     0,    16,    31,    17,    17,
      11,    23,    25,    16,    15,    16,    -1,    18,    19,    20,
      21,    22,    -1,    24,    -1,    -1,    27,    28,    41,    30,
      16,    -1,    18,    19,    20,    21,    22,    -1,    -1,    -1,
      -1,    27,    28,    -1,    30
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,    11,    15,    16,    18,    19,    20,    21,    22,    24,
      27,    28,    30,    33,    34,    35,    37,    39,    40,    41,
      42,    43,    44,    39,     0,    16,    42,    31,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      23,    36,    25,    26,    38,    17,    39,    39,    17
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    32,    33,    34,    34,    35,    35,    35,    35,    35,
      36,    36,    36,    36,    36,    36,    36,    36,    36,    36,
      36,    36,    36,    37,    37,    37,    38,    38,    39,    39,
      40,    41,    41,    42,    42,    43,    43,    44,    44,    44,
      44
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     2,     1,     2,     1,     4,     1,     1,     1,
       3
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "$end", "error", "$undefined", "PROG_OR", "PROG_NOR", "PROG_XOR",
  "PROG_AND", "PROG_NAND", "BITSHIFTLEFT", "BITSHIFTRIGHT", "PLUS",
  "MINUS", "MULTIPLY", "DIVIDE", "MOD", "PROG_NOT", "LEFTPARENTHESIS",
  "RIGHTPARENTHESIS", "SIN", "COS", "TAN", "LOG", "LN", "CARET",
  "SQUAREROOT", "POWER2", "POWER3", "PI", "EULER", "SPACE", "NUMBER",
  "EQU", "$accept", "Program", "command", "trigo_function",
  "binary_operator", "pre_unary_operator", "post_unary_operator",
  "binary_expr", "binary_impl_expr", "unary_pre_expr", "unary_post_expr",
  "funcall_expr", "prim_expr", YY_NULLPTR
  };


  const unsigned short int
  Parser::yyrline_[] =
  {
       0,    67,    67,    74,    78,    88,    92,    96,   100,   104,
     111,   115,   119,   123,   127,   131,   135,   139,   143,   147,
     151,   155,   159,   166,   170,   174,   181,   185,   192,   196,
     206,   212,   216,   223,   228,   236,   240,   250,   254,   258,
     262
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31
    };
    const unsigned int user_token_number_max_ = 286;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy



