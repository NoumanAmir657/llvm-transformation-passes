; ModuleID = 'examples/foo3.ll'
source_filename = "main.c"
target datalayout = "e-m:e-p:64:64-i64:64-i128:128-n32:64-S128"
target triple = "riscv64-unknown-unknown-elf"

@.str = private unnamed_addr constant [6 x i8] c"Hello\00", align 1

define dso_local signext i32 @main() {
entry:
  %retval = alloca i32, align 4
  %i = alloca i32, align 4
  %z = alloca i32, align 4
  store i32 0, ptr %retval, align 4
  store i32 3, ptr %i, align 4
  %0 = load i32, ptr %i, align 4
  %1 = shl i32 %0, 2
  store i32 %1, ptr %z, align 4
  %call = call signext i32 (ptr, ...) @printf(ptr noundef @.str)
  %call1 = call signext i32 (ptr, ...) @printf(ptr noundef @.str)
  ret i32 0
}

declare dso_local signext i32 @printf(ptr noundef, ...)
