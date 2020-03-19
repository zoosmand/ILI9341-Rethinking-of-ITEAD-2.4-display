.syntax unified

.global Delay_Handler
.global Delay


    .section  .text.Delay_Handler
    .type Delay_Handler, %function
Delay_Handler:
  ldr r1, =1000
  adds r0, r1
  bx lr
  .size  Delay_Handler, .-Delay_Handler




    .section  .text.Delay
    .type Delay, %function
Delay:
  ldr r1, =11500
  muls r0, r1
  _LOOP_:
    subs r0, 1
    bpl _LOOP_
  bx lr
  .size  Delay, .-Delay



