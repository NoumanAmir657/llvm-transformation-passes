; RUN: opt -load-pass-plugin ../build/lib/libAddConst.so -passes="add-call" -S %s 2>&1 | FileCheck %s

; ModuleID = 'main.c'
source_filename = "main.c"
target datalayout = "e-m:e-p:64:64-i64:64-i128:128-n32:64-S128"
target triple = "riscv64-unknown-unknown-elf"

@.str = private unnamed_addr constant [6 x i8] c"Hello\00", align 1

; Function Attrs: noinline nounwind optnone
define dso_local signext i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %i = alloca i32, align 4
  %z = alloca i32, align 4
  store i32 0, ptr %retval, align 4
  store i32 3, ptr %i, align 4
  %0 = load i32, ptr %i, align 4
  %mul = mul nsw i32 %0, 4
  store i32 %mul, ptr %z, align 4
  %call = call signext i32 (ptr, ...) @printf(ptr noundef @.str)
  ret i32 0
}

declare dso_local signext i32 @printf(ptr noundef, ...)

; CHECK: call void @__instrument_printf()
; CHECK: call void @__display_printfnum()