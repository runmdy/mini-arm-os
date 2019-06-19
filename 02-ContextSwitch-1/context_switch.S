.thumb
.syntax unified

.global activate
activate:
	/* save kernel state  ip 指令 psr 程式狀態暫存器   */
	mrs ip, psr
	push {r4, r5, r6, r7, r8, r9, r10, r11, ip, lr}

	/* switch to process stack 使用者堆疊 */
	msr psp, r0
	mov r0, #3
	msr control, r0

	/* load user state 載入使用者站存器*/
	pop {r4, r5, r6, r7, r8, r9, r10, r11, lr}

	/* jump to user task 跳到新的真的要執行的暫存區塊 */
	bx lr
