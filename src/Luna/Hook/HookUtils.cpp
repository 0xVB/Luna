#include "Luna/Hook/LunaHook.hpp"

usize getInstructionSize(const u8* bytes, i32** rel32)
{
#define __nextByte *(bytes++)
	const u8* startBytes = bytes;
	bool shortImm = false;

	u8 byte = __nextByte;
	// these are segments
	while (byte == 0xF0 || byte == 0xF2 || byte == 0xF3 || byte == 0x66 || byte == 0x67 || byte == 0x64 || byte == 0x65) {
		if (byte == 0x66)
			shortImm = true;

		byte = __nextByte;
	}

	i32* relPos = 0;

	bool hasModRM = false;
	usize immSize = 0;

#define ___END goto fuckingCompilerLimitEnd;
#define h(x) (0x ## x)
#define rm(x) if (byte == h(x)) {hasModRM = true;___END;}
#define im8(x) if (byte == h(x)) {immSize = 1;___END;}
#define i16(x) if (byte == h(x)) {immSize = 2;___END;}
#define rm8(x) if (byte == h(x)) {hasModRM = true; immSize = 1;___END;}
#define r86(x) if (byte == h(x)) { hasModRM = true; immSize = shortImm ? 2 : 4; ___END;}
#define i86(x) if (byte == h(x)) {immSize = shortImm ? 2 : 4;___END;} 
#define rel(x) if (byte == h(x)) {relPos = (i32*)bytes; bytes += 4; ___END;} 
#define r16_32(x) if (byte == h(x)) {if (shortImm) {bytes += 2;} else {relPos = (i32*)bytes; bytes += 4;}; ___END;} 

#define implSet(x) rm(x) rm(x+1) rm(x+2) rm(x+3) im8(x+4) i86(x+5)
	implSet(0)
		implSet(8)
		if (byte == 0x0F) { // two byte opcodes
			byte = __nextByte;

			rm(1F)
				r16_32(80)
				r16_32(81)
				r16_32(82)
				r16_32(83)
				r16_32(84)
				r16_32(85)
				r16_32(86)
				r16_32(87)
				r16_32(88)
				r16_32(89)
				r16_32(8a)
				r16_32(8b)
				r16_32(8c)
				r16_32(8d)
				r16_32(8e)
				r16_32(8f)

				rm(90)
				rm(91)
				rm(92)
				rm(93)
				rm(94)
				rm(95)
				rm(96)
				rm(97)
				rm(98)
				rm(99)
				rm(9a)
				rm(9b)
				rm(9c)
				rm(9d)
				rm(9e)
				rm(9f)

				rm(B6)
				rm(B7)

				rm8(BA)
				___END;
		}
	implSet(10)
		implSet(18)
		implSet(20)
		implSet(28)
		implSet(30)
		implSet(38)
		i86(68)
		rm(69)
		im8(6A)
		rm8(6B)

		im8(70)
		im8(71)
		im8(72)
		im8(73)
		im8(74)
		im8(75)
		im8(76)
		im8(77)
		im8(78)
		im8(79)
		im8(7a)
		im8(7b)
		im8(7c)
		im8(7d)
		im8(7e)
		im8(7f)


		im8(6A)
		rm8(6B)
		rm8(80)
		r86(81)
		rm8(82)
		rm8(83)
		rm(84)
		rm(85)
		rm(86)
		rm(87)
		rm(88)
		rm(89)
		rm(8a)
		rm(8b)
		rm(8c)
		rm(8d)
		rm(8e)
		rm(8f)

		rel(A0)
		rel(A1)
		rel(A2)
		rel(A3)

		i86(A8)
		i86(A9)

		im8(b0)
		im8(b1)
		im8(b2)
		im8(b3)
		im8(b4)
		im8(b5)
		im8(b6)
		im8(b7)

		i86(b8)
		i86(b9)
		i86(ba)
		i86(bb)
		i86(bc)
		i86(bd)
		i86(be)
		i86(bf)

		rm8(c0)
		rm8(c1)

		i16(c2)

		rm8(c6)
		r86(c7)

		i16(c8)
		i16(CA)
		im8(CD)
		rm(D9)
		rm(DB)
		rel(E8)
		rel(E9)

		im8(EB)

		rm(FE)
		rm(FF)

#undef ___END
#undef h
#undef rm
#undef im8
#undef i16
#undef rm8
#undef r86
#undef i86
#undef rel
#undef r16_32
#undef implSet
		fuckingCompilerLimitEnd :


	/*if (byte == 0xFF) {
u8 modrm = *(bytes + 1);
u8 reg = (modrm >> 3) & 0b111;
} else*/

	if (hasModRM) {
		u8 modrm = __nextByte;
		u8 mod = modrm >> 6;
		u8 rm = modrm & 0b111;
		if (mod != 0b11) {
			bool hasSib = rm == 0b100;
			if (hasSib) __nextByte;
			if (mod == 0b01) __nextByte;
			if (mod == 0b10) bytes += 4;
			if (rm == 0b101 && mod == 0b00) {
				relPos = (i32*)bytes;
				bytes += 4;
			}
		}
	}

#undef __nextByte

	bytes += immSize;
	if (rel32)
		*rel32 = relPos;
	return bytes - startBytes;
}