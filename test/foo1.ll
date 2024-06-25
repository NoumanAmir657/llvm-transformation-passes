; RUN: opt -load-pass-plugin ../build/lib/libAddConst.so -passes="add-metadata" -S %s 2>&1 | FileCheck %s

define dso_local i64 @factorial(i32 noundef signext %n) #0 {
entry:
  %retval = alloca i64, align 8
  %n.addr = alloca i32, align 4
  store i32 %n, ptr %n.addr, align 4
  %0 = load i32, ptr %n.addr, align 4
  %cmp = icmp eq i32 %0, 0
  br i1 %cmp, label %if.then, label %lor.lhs.false

lor.lhs.false:                                    ; preds = %entry
  %1 = load i32, ptr %n.addr, align 4
  %cmp1 = icmp eq i32 %1, 1
  br i1 %cmp1, label %if.then, label %if.else

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i64 1, ptr %retval, align 8
  br label %return

if.else:                                          ; preds = %lor.lhs.false
  %2 = load i32, ptr %n.addr, align 4
  %conv = sext i32 %2 to i64
  %3 = load i32, ptr %n.addr, align 4
  %sub = sub nsw i32 %3, 1
  %call = call i64 @factorial(i32 noundef signext %sub)
  %mul = mul i64 %conv, %call
  store i64 %mul, ptr %retval, align 8
  br label %return

return:                                           ; preds = %if.else, %if.then
  %4 = load i64, ptr %retval, align 8
  ret i64 %4
}

; CHECK: %0 = load i32, ptr %n.addr, align 4, !x10 !0
; CHECK: %1 = load i32, ptr %n.addr, align 4, !x10 !0
; CHECK: %2 = load i32, ptr %n.addr, align 4, !x10 !0
; CHECK: %3 = load i32, ptr %n.addr, align 4, !x10 !0
; CHECK: %4 = load i64, ptr %retval, align 8, !x10 !0