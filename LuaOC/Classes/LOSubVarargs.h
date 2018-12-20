//
//  LOSubVarargs.h
//  LuaOC
//
//  Created by 刘旭 on 2018/12/20.
//

#import "LOVarargs.h"

@interface LOSubVarargs : LOVarargs

- (instancetype)initWithVarargs:(LOVarargs *)varargs start:(int)start end:(int)end;

@end

