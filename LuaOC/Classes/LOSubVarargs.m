//
//  LOSubVarargs.m
//  LuaOC
//
//  Created by 刘旭 on 2018/12/20.
//

#import "LOSubVarargs.h"
#import "LOLuaValue.h"

@interface LOSubVarargs ()

@property (nonatomic, strong) LOVarargs *v;
@property (nonatomic, assign) int start;
@property (nonatomic, assign) int end;

@end
@implementation LOSubVarargs

- (instancetype)initWithVarargs:(LOVarargs *)varargs start:(int)start end:(int)end
{
    if (self = [super init]) {
        _v = varargs;
        _start = start;
        _end = end;
    }
    return self;
}

- (LOLuaValue *)arg:(int)i
{
    i += _start-1;
    return i>=_start && i<=_end? [_v arg:i]: LOLuaValue.NIL;
}

- (LOLuaValue *)arg1
{
    return [_v arg:_start];
}

- (int)narg
{
    return 1 +_end -_start;
}

- (LOVarargs *)subArgs:(int)start
{
    if (start == 1)
        return self;
    int newstart = self.start + start - 1;
    if (start > 0) {
//        if (newstart >= self.end)
//            return LuaValue.NONE;
//        if (newstart == self.end)
//            return v.arg(self.end);
//        if (newstart == self.end-1)
//            return new Varargs.PairVarargs(v.arg(this.end-1), v.arg(this.end));
//        return new SubVarargs(v, newstart, this.end);
    }
//    return new SubVarargs(v, newstart, this.end);
    return nil;
}

@end
