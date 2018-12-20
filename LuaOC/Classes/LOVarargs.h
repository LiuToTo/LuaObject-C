//
//  Varargs.h
//  Expecta
//
//  Created by 刘旭 on 2018/12/19.
//

#import <Foundation/Foundation.h>

@class LOLuaValue;
@class LOLuaClosure;
@class LOLuaFunction;
@class LOLuaNumber;
@class LOLuaInteger;
@class LOLuaString;
@class LOLuaTable;
@class LOLuaThread;
@class LOGlobals;
@class LOLuaError;

/**
 * Class to encapsulate varargs values, either as part of a variable argument list, or multiple return values.
 * <p>
 * To construct varargs, use one of the static methods such as
 * {@code LuaValue.varargsOf(LuaValue,LuaValue)}
 * <p>
 * <p>
 * Any LuaValue can be used as a stand-in for Varargs, for both calls and return values.
 * When doing so, nargs() will return 1 and arg1() or arg(1) will return this.
 * This simplifies the case when calling or implementing varargs functions with only
 * 1 argument or 1 return value.
 * <p>
 * Varargs can also be derived from other varargs by appending to the front with a call
 * such as  {@code LuaValue.varargsOf(LuaValue,Varargs)}
 * or by taking a portion of the args using {@code Varargs.subargs(int start)}
 * <p>
 * @see LuaValue#varargsOf(LuaValue[])
 * @see LuaValue#varargsOf(LuaValue, Varargs)
 * @see LuaValue#varargsOf(LuaValue[], Varargs)
 * @see LuaValue#varargsOf(LuaValue, LuaValue, Varargs)
 * @see LuaValue#varargsOf(LuaValue[], int, int)
 * @see LuaValue#varargsOf(LuaValue[], int, int, Varargs)
 * @see LuaValue#subargs(int)
 */
@interface LOVarargs : NSObject

/**
 * Get the n-th argument value (1-based).
 * @param i the index of the argument to get, 1 is the first argument
 * @return Value at position i, or LuaValue.NIL if there is none.
 * @see Varargs#arg1()
 * @see LuaValue#NIL
 */
- (LOLuaValue *)arg:(int)i;

/**
 * Get the number of arguments, or 0 if there are none.
 * @return number of arguments.
 */
- (int)narg;

/**
 * Get the first argument in the list.
 * @return LuaValue which is first in the list, or LuaValue.NIL if there are no values.
 * @see Varargs#arg(int)
 * @see LuaValue#NIL
 */
- (LOLuaValue *)arg1;

/**
 * Evaluate any pending tail call and return result.
 * @return the evaluated tail call result
 */
- (LOVarargs *)eval;

/**
 * Return true if this is a TailcallVarargs
 * @return true if a tail call, false otherwise
 */
- (BOOL)isTailcall;

// -----------------------------------------------------------------------
// utilities to get specific arguments and type-check them.
// -----------------------------------------------------------------------

/** Gets the type of argument {@code i}
 * @param i the index of the argument to convert, 1 is the first argument
 * @return int value corresponding to one of the LuaValue integer type values
 * @see LuaValue#TNIL
 * @see LuaValue#TBOOLEAN
 * @see LuaValue#TNUMBER
 * @see LuaValue#TSTRING
 * @see LuaValue#TTABLE
 * @see LuaValue#TFUNCTION
 * @see LuaValue#TUSERDATA
 * @see LuaValue#TTHREAD
 * */
- (int)type:(int)i;

/** Tests if argument i is nil.
 * @param i the index of the argument to test, 1 is the first argument
 * @return true if the argument is nil or does not exist, false otherwise
 * @see LuaValue#TNIL
 * */
- (BOOL)isNil:(int)i;

/** Tests if argument i is a function.
 * @param i the index of the argument to test, 1 is the first argument
 * @return true if the argument exists and is a function or closure, false otherwise
 * @see LuaValue#TFUNCTION
 * */
- (BOOL)isFunction:(int)i;

/** Tests if argument i is a number.
 * Since anywhere a number is required, a string can be used that
 * is a number, this will return true for both numbers and
 * strings that can be interpreted as numbers.
 * @param i the index of the argument to test, 1 is the first argument
 * @return true if the argument exists and is a number or
 * string that can be interpreted as a number, false otherwise
 * @see LuaValue#TNUMBER
 * @see LuaValue#TSTRING
 * */
- (BOOL)isNumber:(int)i;

/** Tests if argument i is a string.
 * Since all lua numbers can be used where strings are used,
 * this will return true for both strings and numbers.
 * @param i the index of the argument to test, 1 is the first argument
 * @return true if the argument exists and is a string or number, false otherwise
 * @see LuaValue#TNUMBER
 * @see LuaValue#TSTRING
 * */
- (BOOL)isString:(int)i;

/** Tests if argument i is a table.
 * @param i the index of the argument to test, 1 is the first argument
 * @return true if the argument exists and is a lua table, false otherwise
 * @see LuaValue#TTABLE
 * */
- (BOOL)isTable:(int)i;

/** Tests if argument i is a thread.
 * @param i the index of the argument to test, 1 is the first argument
 * @return true if the argument exists and is a lua thread, false otherwise
 * @see LuaValue#TTHREAD
 * */
- (BOOL)isThread:(int)i;

/** Tests if argument i is a userdata.
 * @param i the index of the argument to test, 1 is the first argument
 * @return true if the argument exists and is a userdata, false otherwise
 * @see LuaValue#TUSERDATA
 * */
- (BOOL)isUserData:(int)i;

/** Tests if a value exists at argument i.
 * @param i the index of the argument to test, 1 is the first argument
 * @return true if the argument exists, false otherwise
 * */
- (BOOL)isValue:(int)i;

/** Return argument i as a boolean value, {@code defval} if nil, or throw a LuaError if any other type.
 * @param i the index of the argument to test, 1 is the first argument
 * @return true if argument i is boolean true, false if it is false, or defval if not supplied or nil
 * @exception LuaError if the argument is not a lua boolean
 * */
- (BOOL)optBoolean:(int)i defval:(BOOL)defval;

/** Return argument i as a closure, {@code defval} if nil, or throw a LuaError if any other type.
 * @param i the index of the argument to test, 1 is the first argument
 * @return LuaClosure if argument i is a closure, or defval if not supplied or nil
 * @exception LuaError if the argument is not a lua closure
 * */
- (LOLuaClosure *)optClosure:(int)i defval:(LOLuaClosure *)defval;

/** Return argument i as a double, {@code defval} if nil, or throw a LuaError if it cannot be converted to one.
 * @param i the index of the argument to test, 1 is the first argument
 * @return  double value if argument i is a number or string that converts to a number, or defval if not supplied or nil
 * @exception LuaError if the argument is not a number
 * */
- (double)optDouble:(int)i defval:(double)defval;

/** Return argument i as a function, {@code defval} if nil, or throw a LuaError  if an incompatible type.
 * @param i the index of the argument to test, 1 is the first argument
 * @return LuaValue that can be called if argument i is lua function or closure, or defval if not supplied or nil
 * @exception LuaError if the argument is not a lua function or closure
 * */
- (LOLuaFunction *)optFunction:(int)i defval:(LOLuaFunction *)defval;

/** Return argument i as a int value, discarding any fractional part, {@code defval} if nil, or throw a LuaError  if not a number.
 * @param i the index of the argument to test, 1 is the first argument
 * @return int value with fraction discarded and truncated if necessary if argument i is number, or defval if not supplied or nil
 * @exception LuaError if the argument is not a number
 * */
- (int)optInt:(int)i defval:(int)defval;

/** Return argument i as a int value, {@code defval} if nil, or throw a LuaError  if not a number or is not representable by a  int.
 * @param i the index of the argument to test, 1 is the first argument
 * @return LuaInteger value that fits in a  int without rounding, or defval if not supplied or nil
 * @exception LuaError if the argument cannot be represented by a  int value
 * */
- (LOLuaInteger *)optInteger:(int)i defval:(LOLuaInteger *)defval;

/** Return argument i as a long value, discarding any fractional part, {@code defval} if nil, or throw a LuaError  if not a number.
 * @param i the index of the argument to test, 1 is the first argument
 * @return long value with fraction discarded and truncated if necessary if argument i is number, or defval if not supplied or nil
 * @exception LuaError if the argument is not a number
 * */
- (long)optLong:(int)i defval:(long)defval;

/** Return argument i as a LuaNumber, {@code defval} if nil, or throw a LuaError  if not a number or string that can be converted to a number.
 * @param i the index of the argument to test, 1 is the first argument, or defval if not supplied or nil
 * @return LuaNumber if argument i is number or can be converted to a number
 * @exception LuaError if the argument is not a number
 * */
- (LOLuaNumber *)optNumber:(int)i defval:(LOLuaNumber *)defval;

/** Return argument i as a NSString if a string or number, {@code defval} if nil, or throw a LuaError  if any other type
 * @param i the index of the argument to test, 1 is the first argument
 * @return String value if argument i is a string or number, or defval if not supplied or nil
 * @exception LuaError if the argument is not a string or number
 * */
- (NSString *)optNSString:(int)i defval:(NSString *)defval;

/** Return argument i as a LuaString if a string or number, {@code defval} if nil, or throw a LuaError  if any other type
 * @param i the index of the argument to test, 1 is the first argument
 * @return LuaString value if argument i is a string or number, or defval if not supplied or nil
 * @exception LuaError if the argument is not a string or number
 * */
- (LOLuaString *)optString:(int)i defval:(LOLuaString *)defval;

/** Return argument i as a LuaTable if a lua table, {@code defval} if nil, or throw a LuaError  if any other type.
 * @param i the index of the argument to test, 1 is the first argument
 * @return LuaTable value if a table, or defval if not supplied or nil
 * @exception LuaError if the argument is not a lua table
 * */
- (LOLuaTable *)optTable:(int)i defval:(LOLuaTable *)defval;

/** Return argument i as a LuaThread if a lua thread, {@code defval} if nil, or throw a LuaError  if any other type.
 * @param i the index of the argument to test, 1 is the first argument
 * @return LuaThread value if a thread, or defval if not supplied or nil
 * @exception LuaError if the argument is not a lua thread
 * */
- (LOLuaThread *)optThread:(int)i defval:(LOLuaThread *)defval;

/** Return argument i as a id Object if a userdata, {@code defval} if nil, or throw a LuaError  if any other type.
 * @param i the index of the argument to test, 1 is the first argument
 * @return id Object value if argument i is a userdata, or defval if not supplied or nil
 * @exception LuaError if the argument is not a userdata
 * */
- (id)optUserData:(int)i defval:(id)defval;

/** Return argument i as a id Object if it is a userdata whose instance Class c or a subclass,
 * {@code defval} if nil, or throw a LuaError  if any other type.
 * @param i the index of the argument to test, 1 is the first argument
 * @param c the class to which the userdata instance must be assignable
 * @return java Object value if argument i is a userdata whose instance Class c or a subclass, or defval if not supplied or nil
 * @exception LuaError if the argument is not a userdata or from whose instance c is not assignable
 * */
- (id)optUserData:(int)i clazz:(Class)c defval:(id)defval;

/** Return argument i as a LuaValue if it exists, or {@code defval}.
 * @param i the index of the argument to test, 1 is the first argument
 * @return LuaValue value if the argument exists, defval if not
 * @exception LuaError if the argument does not exist.
 * */
- (LOLuaValue *)optValue:(int)i defval:(LOLuaValue *)defval;

/** Return argument i as a boolean value, or throw an error if any other type.
 * @param i the index of the argument to test, 1 is the first argument
 * @return true if argument i is boolean true, false if it is false
 * @exception LuaError if the argument is not a lua boolean
 * */
- (BOOL)checkBoolean:(int)i;

/** Return argument i as a closure, or throw an error if any other type.
 * @param i the index of the argument to test, 1 is the first argument
 * @return LuaClosure if argument i is a closure.
 * @exception LuaError if the argument is not a lua closure
 * */
- (LOLuaClosure *)checkClosure:(int)i;

/** Return argument i as a double, or throw an error if it cannot be converted to one.
 * @param i the index of the argument to test, 1 is the first argument
 * @return java double value if argument i is a number or string that converts to a number
 * @exception LuaError if the argument is not a number
 * */
- (double)checkDouble:(int)i;

/** Return argument i as a function, or throw an error if an incompatible type.
 * @param i the index of the argument to test, 1 is the first argument
 * @return LuaValue that can be called if argument i is lua function or closure
 * @exception LuaError if the argument is not a lua function or closure
 * */
- (LOLuaFunction *)checkFunction:(int)i;

/** Return argument i as a java int value, discarding any fractional part, or throw an error if not a number.
 * @param i the index of the argument to test, 1 is the first argument
 * @return int value with fraction discarded and truncated if necessary if argument i is number
 * @exception LuaError if the argument is not a number
 * */
- (int)checkInt:(int)i;

/** Return argument i as a java int value, or throw an error if not a number or is not representable by a java int.
 * @param i the index of the argument to test, 1 is the first argument
 * @return LuaInteger value that fits in a java int without rounding
 * @exception LuaError if the argument cannot be represented by a java int value
 * */
- (LOLuaInteger *)checkInteger:(int)i;

/** Return argument i as a java long value, discarding any fractional part, or throw an error if not a number.
 * @param i the index of the argument to test, 1 is the first argument
 * @return long value with fraction discarded and truncated if necessary if argument i is number
 * @exception LuaError if the argument is not a number
 * */
- (long)checkLong:(int)i;           

/** Return argument i as a LuaNumber, or throw an error if not a number or string that can be converted to a number.
 * @param i the index of the argument to test, 1 is the first argument
 * @return LuaNumber if argument i is number or can be converted to a number
 * @exception LuaError if the argument is not a number
 * */
- (LOLuaNumber *)checkNumber:(int)i;

/** Return argument i as a java String if a string or number, or throw an error if any other type
 * @param i the index of the argument to test, 1 is the first argument
 * @return String value if argument i is a string or number
 * @exception LuaError if the argument is not a string or number
 * */
- (NSString *)checkNSString:(int)i;

/** Return argument i as a LuaString if a string or number, or throw an error if any other type
 * @param i the index of the argument to test, 1 is the first argument
 * @return LuaString value if argument i is a string or number
 * @exception LuaError if the argument is not a string or number
 * */
- (LOLuaString *)checkString:(int)i;

/** Return argument i as a LuaTable if a lua table, or throw an error if any other type.
 * @param i the index of the argument to test, 1 is the first argument
 * @return LuaTable value if a table
 * @exception LuaError if the argument is not a lua table
 * */
- (LOLuaTable *)checkTable:(int)i;

/** Return argument i as a LuaThread if a lua thread, or throw an error if any other type.
 * @param i the index of the argument to test, 1 is the first argument
 * @return LuaThread value if a thread
 * @exception LuaError if the argument is not a lua thread
 * */
- (LOLuaThread *)checkThread:(int)i;

/** Return argument i as a java Object if a userdata, or throw an error if any other type.
 * @param i the index of the argument to test, 1 is the first argument
 * @return java Object value if argument i is a userdata
 * @exception LuaError if the argument is not a userdata
 * */
- (id)checkUserData:(int)i;

/** Return argument i as a java Object if it is a userdata whose instance Class c or a subclass,
 * or throw an error if any other type.
 * @param i the index of the argument to test, 1 is the first argument
 * @param c the class to which the userdata instance must be assignable
 * @return java Object value if argument i is a userdata whose instance Class c or a subclass
 * @exception LuaError if the argument is not a userdata or from whose instance c is not assignable
 * */
- (id)checkUserData:(int)i clazz:(Class)c;

/** Return argument i as a LuaValue if it exists, or throw an error.
 * @param i the index of the argument to test, 1 is the first argument
 * @return LuaValue value if the argument exists
 * @exception LuaError if the argument does not exist.
 * */
- (id)checkValue:(int)i;

/** Return argument i as a LuaValue if it is not nil, or throw an error if it is nil.
 * @param i the index of the argument to test, 1 is the first argument
 * @return LuaValue value if the argument is not nil
 * @exception LuaError if the argument doesn't exist or evaluates to nil.
 * */
- (LOLuaValue *)checkNotNil:(int)i;

/** Performs test on argument i as a LuaValue when a user-supplied assertion passes, or throw an error.
 * Returns normally if the value of {@code test} is {@code true}, otherwise throws and argument error with
 * the supplied message, {@code msg}.
 * @param test user supplied assertion to test against
 * @param i the index to report in any error message
 * @param msg the error message to use when the test fails
 * @exception LuaError if the the value of {@code test} is {@code false}
 * */
- (void)argCheck:(BOOL)test index:(int)i message:(NSString *)msg;

/** Return true if there is no argument or nil at argument i.
 * @param i the index of the argument to test, 1 is the first argument
 * @return true if argument i contains either no argument or nil
 * */
- (BOOL)isNoneOrNil:(int)i;

/** Convert argument {@code i} to java boolean based on lua rules for boolean evaluation.
 * @param i the index of the argument to convert, 1 is the first argument
 * @return {@code false} if argument i is nil or false, otherwise {@code true}
 * */
- (BOOL)toBoolean:(int)i;

/** Return argument i as a java byte value, discarding any fractional part and truncating,
 * or 0 if not a number.
 * @param i the index of the argument to convert, 1 is the first argument
 * @return byte value with fraction discarded and truncated if necessary if argument i is number, otherwise 0
 * */
- (Byte)toByte:(int)i;

/** Return argument i as a java char value, discarding any fractional part and truncating,
 * or 0 if not a number.
 * @param i the index of the argument to convert, 1 is the first argument
 * @return char value with fraction discarded and truncated if necessary if argument i is number, otherwise 0
 * */
- (char)toChar;

/** Return argument i as a java double value or 0 if not a number.
 * @param i the index of the argument to convert, 1 is the first argument
 * @return double value if argument i is number, otherwise 0
 * */
- (double)toDouble:(int)i;

/** Return argument i as a java float value, discarding excess fractional part and truncating,
 * or 0 if not a number.
 * @param i the index of the argument to convert, 1 is the first argument
 * @return float value with excess fraction discarded and truncated if necessary if argument i is number, otherwise 0
 * */
- (float)toFloat:(int)i;

/** Return argument i as a java int value, discarding any fractional part and truncating,
 * or 0 if not a number.
 * @param i the index of the argument to convert, 1 is the first argument
 * @return int value with fraction discarded and truncated if necessary if argument i is number, otherwise 0
 * */
- (int)toInt:(int)i;

/** Return argument i as a java long value, discarding any fractional part and truncating,
 * or 0 if not a number.
 * @param i the index of the argument to convert, 1 is the first argument
 * @return long value with fraction discarded and truncated if necessary if argument i is number, otherwise 0
 * */
- (long)toLong:(int)i;

/** Return argument i as a java String based on the type of the argument.
 * @param i the index of the argument to convert, 1 is the first argument
 * @return String value representing the type
 * */
- (NSString *)toNSString:(int)i;

/** Return argument i as a java short value, discarding any fractional part and truncating,
 * or 0 if not a number.
 * @param i the index of the argument to convert, 1 is the first argument
 * @return short value with fraction discarded and truncated if necessary if argument i is number, otherwise 0
 * */
- (short)toShort:(int)i;

/** Return argument i as a java Object if a userdata, or null.
 * @param i the index of the argument to convert, 1 is the first argument
 * @return java Object value if argument i is a userdata, otherwise null
 * */
- (id)toUserData:(int)i;

/** Return argument i as a java Object if it is a userdata whose instance Class c or a subclass, or null.
 * @param i the index of the argument to convert, 1 is the first argument
 * @param c the class to which the userdata instance must be assignable
 * @return java Object value if argument i is a userdata whose instance Class c or a subclass, otherwise null
 * */
- (id)toUserData:(int)i clazz:(Class)c;

/** Convert the list of varargs values to a human readable java String.
 * @return String value in human readable form such as {1,2}.
 */
- (NSString *)toNSString;

/** Convert the value or values to a java String using Varargs.tojstring()
 * @return String value in human readable form.
 * @see Varargs#tojstring()
 */
- (NSString *)toString;

/**
 * Create a {@code Varargs} instance containing arguments starting at index {@code start}
 * @param start the index from which to include arguments, where 1 is the first argument.
 * @return Varargs containing argument { start, start+1,  ... , narg-start-1 }
 */
- (LOVarargs *)subArgs:(int)start;








































@end
