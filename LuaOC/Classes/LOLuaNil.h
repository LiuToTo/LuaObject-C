//
//  LOLuaNil.h
//  LuaOC
//
//  Created by 刘旭 on 2018/12/20.
//

#import "LOLuaValue.h"

/**
 * Class to encapsulate behavior of the singleton instance {@code nil}
 * <p>
 * There will be one instance of this class, {@link LuaValue#NIL},
 * per Java virtual machine.
 * However, the {@link Varargs} instance {@link LuaValue#NONE}
 * which is the empty list,
 * is also considered treated as a nil value by default.
 * <p>
 * Although it is possible to test for nil using Java == operator,
 * the recommended approach is to use the method {@link LuaValue#isnil()}
 * instead.  By using that any ambiguities between
 * {@link LuaValue#NIL} and {@link LuaValue#NONE} are avoided.
 * @see LuaValue
 * @see LuaValue#NIL
 */
@interface LOLuaNil : LOLuaValue

+ (instancetype)defaultNil;

@end
