#ifndef JIT_RUNNER_COMPILED_BLOCKS_H
#define JIT_RUNNER_COMPILED_BLOCKS_H


// preparing
//    728:	55                   	push   %rbp
//    729:	48 89 e5             	mov    %rsp,%rbp
//    72c:	53                   	push   %rbx
//    72d:	48 83 ec 38          	sub    $0x38,%rsp
//    731:	48 89 7d d8          	mov    %rdi,-0x28(%rbp)
//    735:	48 89 75 d0          	mov    %rsi,-0x30(%rbp)
//    739:	48 89 55 c8          	mov    %rdx,-0x38(%rbp)
//    73d:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
//    741:	bf 80 38 01 00       	mov    $0x13880,%edi
//    746:	ff d0                	callq  *%rax
//    748:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
//    74c:	c7 45 e4 00 00 00 00 	movl   $0x0,-0x1c(%rbp)

unsigned char preparing[] = {
        0x55,
        0x48, 0x89, 0xe5,
        0x53,
        0x48, 0x83, 0xec, 0x38,
        0x48, 0x89, 0x7d, 0xd8,
        0x48, 0x89, 0x75, 0xd0,
        0x48, 0x89, 0x55, 0xc8,
        0x48, 0x8b, 0x45, 0xc8,
        0xbf, 0x80, 0x38, 0x81, 0x00,
//            0xbf, 0x88, 0x80, 0x00, 0x00,
        0xff, 0xd0,
        0x48, 0x89, 0x45, 0xe8,
        0xc7, 0x45, 0xe4, 0x00, 0x00, 0x00, 0x00
};


//    index++;

//    753:	83 45 e4 01          	addl   $0x1,-0x1c(%rbp)

unsigned char indexincr[] = {
        0x83, 0x45, 0xe4, 0x01
};



//    ar[index]++;

//    763:	8b 45 e4             	mov    -0x1c(%rbp),%eax
//    766:	48 98                	cltq
//    768:	48 8d 14 85 00 00 00 	lea    0x0(,%rax,4),%rdx
//    76f:	00
//    770:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
//    774:	48 01 d0             	add    %rdx,%rax
//    777:	8b 10                	mov    (%rax),%edx
//    779:	83 c2 01             	add    $0x1,%edx
//    77c:	89 10                	mov    %edx,(%rax)

unsigned char arincr[] = {
        0x8b, 0x45, 0xe4,
        0x48, 0x98,
        0x48, 0x8d, 0x14, 0x85, 0x00, 0x00, 0x00,
        0x00,
        0x48, 0x8b, 0x45, 0xe8,
        0x48, 0x01, 0xd0,
        0x8b, 0x10,
        0x83, 0xc2, 0x01,
        0x89, 0x10
};


//    putchar(ar[index]);

//    7cf:	8b 45 e4             	mov    -0x1c(%rbp),%eax
//    7d2:	48 98                	cltq
//    7d4:	48 8d 14 85 00 00 00 	lea    0x0(,%rax,4),%rdx
//    7db:	00
//    7dc:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
//    7e0:	48 01 d0             	add    %rdx,%rax
//    7e3:	8b 10                	mov    (%rax),%edx
//    7e5:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
//    7e9:	89 d7                	mov    %edx,%edi
//    7eb:	ff d0                	callq  *%rax

unsigned char ptchr[] = {
        0x8b, 0x45, 0xe4,
        0x48, 0x98,
        0x48, 0x8d, 0x14, 0x85, 0x00, 0x00, 0x00,
        0x00,
        0x48, 0x8b, 0x45, 0xe8,
        0x48, 0x01, 0xd0,
        0x8b, 0x10,
        0x48, 0x8b, 0x45, 0xd8,
        0x89, 0xd7,
        0xff, 0xd0
};


//    index--;

//    865:	83 6d e4 01          	subl   $0x1,-0x1c(%rbp)

unsigned char indexdec[] = {
        0x83, 0x6d, 0xe4, 0x01
};


//    ar[index]--;

//    875:	8b 45 e4             	mov    -0x1c(%rbp),%eax
//    878:	48 98                	cltq
//    87a:	48 8d 14 85 00 00 00 	lea    0x0(,%rax,4),%rdx
//    881:	00
//    882:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
//    886:	48 01 d0             	add    %rdx,%rax
//    889:	8b 10                	mov    (%rax),%edx
//    88b:	83 ea 01             	sub    $0x1,%edx
//    88e:	89 10                	mov    %edx,(%rax)

unsigned char ardec[] = {
        0x8b, 0x45, 0xe4,
        0x48, 0x98,
        0x48, 0x8d, 0x14, 0x85, 0x00, 0x00, 0x00,
        0x00,
        0x48, 0x8b, 0x45, 0xe8,
        0x48, 0x01, 0xd0,
        0x8b, 0x10,
        0x83, 0xea, 0x01,
        0x89, 0x10
};


//    ar[index] = getchar();

//    8e1:	8b 45 e4             	mov    -0x1c(%rbp),%eax
//    8e4:	48 98                	cltq
//    8e6:	48 8d 14 85 00 00 00 	lea    0x0(,%rax,4),%rdx
//    8ed:	00
//    8ee:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
//    8f2:	48 8d 1c 02          	lea    (%rdx,%rax,1),%rbx
//    8f6:	48 8b 55 d0          	mov    -0x30(%rbp),%rdx
//    8fa:	b8 00 00 00 00       	mov    $0x0,%eax
//    8ff:	ff d2                	callq  *%rdx
//    901:	89 03                	mov    %eax,(%rbx)

unsigned char gtchr[] = {
        0x8b, 0x45, 0xe4,
        0x48, 0x98,
        0x48, 0x8d, 0x14, 0x85, 0x00, 0x00, 0x00,
        0x00,
        0x48, 0x8b, 0x45, 0xe8,
        0x48, 0x8d, 0x1c, 0x02,
        0x48, 0x8b, 0x55, 0xd0,
        0xb8, 0x00, 0x00, 0x00, 0x00,
        0xff, 0xd2,
        0x89, 0x03
};


//    ending

//    969:	90                   	nop
//    96a:	48 83 c4 38          	add    $0x38,%rsp
//    96e:	5b                   	pop    %rbx
//    96f:	5d                   	pop    %rbp
//    970:	c3                   	retq

unsigned char ending[] = {
        0x90,
        0x48, 0x83, 0xc4, 0x38,
        0x5b,
        0x5d,
        0xc3
};


//    jmp

//    83f:	e9 75 02 00 00       	jmpq   ab9 <fnc+0x3cf>

unsigned char jmp_code[] = {
        0xe9, 0x00, 0x00, 0x00, 0x00
};


//    jne

//    ab9:	8b 45 e4             	mov    -0x1c(%rbp),%eax
//    abc:	48 98                	cltq
//    abe:	48 8d 14 85 00 00 00 	lea    0x0(,%rax,4),%rdx
//    ac5:	00
//    ac6:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
//    aca:	48 01 d0             	add    %rdx,%rax
//    acd:	8b 00                	mov    (%rax),%eax
//
//    acf:	85 c0                	test   %eax,%eax
//    ad1:	0f 85 6d fd ff ff    	jne    844 <fnc+0x15a>

unsigned char jne_code[] = {
        0x8b, 0x45, 0xe4,
        0x48, 0x98,
        0x48, 0x8d, 0x14, 0x85, 0x00, 0x00, 0x00,
        0x00,
        0x48, 0x8b, 0x45, 0xe8,
        0x48, 0x01, 0xd0,
        0x8b, 0x00,
        0x85, 0xc0,
        0x0f, 0x85, 0x00, 0x00, 0x00, 0x00
};


#endif //JIT_RUNNER_COMPILED_BLOCKS_H
