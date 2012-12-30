#ifndef __ELF_H__
#define __ELF_H__

#define MAX_PHNUM	10	//максимальное количество програмных сегментов

typedef unsigned long  Elf32_Addr;	//Unsigned program address 4
typedef unsigned short Elf32_Half;	//Unsigned medium integer  2
typedef unsigned long  Elf32_Off; 	//Unsigned file offset     4
typedef          long  Elf32_Sword; 	//Signed large integer     4
typedef unsigned long  Elf32_Word; 	//Unsigned large integer   4

//ELF Header
//e_ident[] Identification Indexes
#define EI_MAG0    0  //File identification
#define EI_MAG1    1  //File identification
#define EI_MAG2    2  //File identification
#define EI_MAG3    3  //File identification
#define EI_CLASS   4  //File class
#define EI_DATA    5  //Data encoding
#define EI_VERSION 6  //File version
#define EI_PAD     7  //Start of padding bytes
#define EI_NIDENT  16 //Size of e_ident[]

typedef struct{
  unsigned char e_ident[EI_NIDENT]; //The initial bytes mark the file as an object file and provide machine-independent data with which to decode and interpret the fileТs contents.
  Elf32_Half e_type;      //This member identifies the object file type.
  Elf32_Half e_machine;   //This memberТs value specifies the required architecture for an individual file.
  Elf32_Word e_version;   //This member identifies the object file version.
  Elf32_Addr e_entry;     //This member gives the virtual address to which the system first transfers control, thus starting the process. If the file has no associated entry point, this member holds zero.
  Elf32_Off  e_phoff;     //This member holds the program header tableТs file offset in bytes. If the file has no program header table, this member holds zero.
  Elf32_Off  e_shoff;     //This member holds the section header tableТs file offset in bytes. If the file has no section header table, this member holds zero.
  Elf32_Word e_flags;     //This member holds processor-specific flags associated with the file. Flag names take the form EF_machine_flag.
  Elf32_Half e_ehsize;    //This member holds the ELF headerТs size in bytes.
  Elf32_Half e_phentsize; //This member holds the size in bytes of one entry in the fileТs program header table; all entries are the same size.
  Elf32_Half e_phnum;     //This member holds the number of entries in the program header table. Thus the product of e_phentsize and e_phnum gives the tableТs size in bytes. If a file has no program header table, e_phnum holds the value zero.
  Elf32_Half e_shentsize; //This member holds a section headerТs size in bytes. A section header is one entry in the section header table; all entries are the same size.
  Elf32_Half e_shnum;     //shnumЧThis member holds the number of entries in the section header table. Thus the product of e_shentsize and e_shnum gives the section header tableТs size in bytes. If a file has no section header table, e_shnum holds the value zero.
  Elf32_Half e_shstrndx;  //This member holds the section header table index of the entry associated with the section name string table. If the file has no section name string table, this member holds the value SHN_UNDEF.
} Elf32_Ehdr;

//E_typeЧThis member identifies the object file type.
#define ET_NONE   0        //No file type
#define ET_REL    1        //Re-locatable file
#define ET_EXEC   2        //Executable file
#define ET_DYN    3        //Shared object file
#define ET_CORE   4        //Core file
#define ET_LOPROC 0xFF00   //Processor-specific
#define ET_HIPROC 0xFFFF   //Processor-specific

//E_machineЧThis memberТs value specifies the required architecture for an individual file.
#define EM_NONE        0  //No machine
#define EM_M32         1  //AT&T WE 32100
#define EM_SPARC       2  //SPARC
#define EM_386         3  //Intel Architecture
#define EM_68K         4  //Motorola 68000
#define EM_88K         5  //Motorola 88000
#define EM_860         7  //Intel 80860
#define EM_MIPS        8  //MIPS RS3000 Big-Endian
#define EM_MIPS_RS4_BE 10 //MIPS RS4000 Big-Endian
#define EM_ARM         40 //ARM/Thumb Architecture

//E_versionЧThis member identifies the object file version.
#define EV_NONE    0 //Invalid version
#define EV_CURRENT 1 //Current version

//EI_MAG0 0 to EI_MAG3ЧA fileТs first 4 bytes hold a magic number, identifying the file as an ELF object file. Name Value Meaning
#define ELFMAG0  0x7f //e_ident[EI_MAG0]
#define ELFMAG1 'E'   //e_ident[EI_MAG1]
#define ELFMAG2 'L'   //e_ident[EI_MAG2]
#define ELFMAG3 'F'   //e_ident[EI_MAG3]

//EI_CLASSЧThe next byte, e_ident[EI_CLASS], identifies the fileТs class, or capacity. Name Value Meaning
#define ELFCLASSNONE 0 //Invalid class
#define ELFCLASS32   1 //32-bit objects
#define ELFCLASS64   2 //64-bit objects

//EI_DATAЧByte e_ident[EI_DATA]specifies the data encoding of all data1 in the object file. The following encodings are currently defined. Name Value Meaning
#define ELFDATANONE 0 //Invalid data encoding
#define ELFDATA2LSB 1 //See Data encodings ELFDATA2LSB, below
#define ELFDATA2MSB 2 //See Data encodings ELFDATA2MSB, below

//Sections
//Section Header
typedef struct{
  Elf32_Word sh_name;      //This member specifies the name of the section. Its value is an index into the section header string table section [see section 3.4, String Table below], giving the location of a null-terminated string.
  Elf32_Word sh_type;      //typeЧThis member categorizes the sectionТs contents and semantics. Section types and their descriptions appear in Figure 3-9 below.
  Elf32_Word sh_flags;     //Sections support 1-bit flags that describe miscellaneous attributes. Flag definitions appear in Figure 3-11, below.
  Elf32_Addr sh_addr;      //If the section will appear in the memory image of a process, this member gives the address at which the sectionТs first byte should reside. Otherwise, the member contains 0.
  Elf32_Off  sh_offset;    //This memberТs value gives the byte offset from the beginning of the file to the first byte in the section. One section type, SHT_NOBITS described in Figure 3-9 below, occupies no space in the file, and its sh_offset member locates the conceptual placement in the file.
  Elf32_Word sh_size;      //This member gives the sectionТs size in bytes. Unless the section type is SHT_NOBITS, the section occupies sh_size bytes in the file. A section of type SHT_NOBITS may have a non-zero size, but it occupies no space in the file.
  Elf32_Word sh_link;      //This member holds a section header table index link, whose interpretation depends on the section type. Figure 3-12 below describes the values.
  Elf32_Word sh_info;      //This member holds extra information, whose interpretation depends on the section type. Figure 3-12 below describes the values.
  Elf32_Word sh_addralign; //Some sections have address alignment constraints. For example, if a section holds a doubleword, the system must ensure double-word alignment for the entire section. That is, the value of sh_addr must be congruent to 0, modulo the value of sh_addralign. Currently, only 0 and positive integral powers of two are allowed. Values 0 and 1 mean the section has no alignment constraints.
  Elf32_Word sh_entsize;   //Some sections hold a table of fixed-size entries, such as a symbol table. For such a section, this member gives the size in bytes of each entry. The member contains 0 if the section does not hold a table of fixedsize entries. A section headerТs sh_type member specifies the sectionТs semantics.
} Elf32_Shdr;

//Special Section Indexes
#define SHN_UNDEF     0     //This value marks an undefined, missing, irrelevant, or otherwise meaningless section reference. For example, a symbol УdefinedФ relative to section number SHN_UNDEF is an undefined symbol.
#define SHN_LORESERVE 0xff00 //This value specifies the lower bound of the range of reserved indexes.
#define SHN_LOPROC    0xff00 //Values in this range are reserved for processor-specific semantics.
#define SHN_HIPROC    0xff1f //Values in this range are reserved for processor-specific semantics.
#define SHN_ABS       0xfff1 //This value specifies absolute values for the corresponding reference. For example, symbols defined relative to section number SHN_ABS have absolute values and are not affected by relocation.
#define SHN_COMMON    0xfff2 //Symbols defined relative to this section are common symbols, such as FORTRAN COMMON or unallocated C external variables.
#define SHN_HIRESERVE 0xffff //This value specifies the upper bound of the range of reserved indexes. The system reserves indexes between SHN_LORESERVE and SHN_HIRESERVE, inclusive; the values do not refer to the section header table. That is, the section header table does not contain entries for the reserved indexes.

//sh_type
#define SHT_NULL     0  //This value marks a section header that does not have an associated section. Other members of the section header have undefined values
#define SHT_PROGBITS 1  //The section holds information defined by the program, whose format and meaning are determined solely by the program.
#define SHT_SYMTAB   2  //The section holds a symbol table.
#define SHT_STRTAB   3  //The section holds a string table.
#define SHT_RELA     4  //The section holds relocation entries with explicit addends, such as type Elf32_Rela for the 32-bit class of object files. An object file may have multiple relocation sections. See Relocation below for details.
#define SHT_HASH     5  //The section holds a symbol hash table.
#define SHT_DYNAMIC  6  //The section holds information for dynamic linking.
#define SHT_NOTE     7  //This section holds information that marks the file in some way.
#define SHT_NOBITS   8  //A section of this type occupies no space in the file but otherwise resembles SHT_PROGBITS. Although this section contains no bytes, the sh_offset member contains the conceptual file offset.
#define SHT_REL      9  //The section holds relocation entries without explicit addends, such as type Elf32_Rel for the 32-bit class of object files. An object file may have multiple relocation sections. See Relocation below for details.
#define SHT_SHLIB    10 //This section type is reserved but has unspecified semantics.
#define SHT_DYNSYM   11 //The section holds a symbol table.
#define SHT_LOPROC   0x70000000
#define SHT_HIPROC   0x7fffffff //Values in this inclusive range are reserved for processor-specific semantics.
#define SHT_LOUSER   0x80000000
#define SHT_HIUSER   0xffffffff //Values in this inclusive range are reserved for application programs. Types between SHT_LOUSER and SHT_HIUSER may be used by an application,without conflicting with current or future system-defined section types.

//Section Attribute Flags, sh_flags
#define SHF_WRITE     1          //The section contains data that should be writable during process execution
#define SHF_ALLOC     2          //The section occupies memory during process execution. Some control sections do not reside in the memory image of an object file; this attribute is off for those sections
#define SHF_EXECINSTR 4          //The section contains executable machine instructions.
#define SHF_MASKPROC  0xf0000000 //Bits in this mask are reserved for processor-specific semantics.

//Program
//Program Header
typedef struct{
  Elf32_Word p_type;   //This member tells what kind of segment this array element describes or how to interpret the array element's information. Type values and their meanings are given in Figure 3-21, below.
  Elf32_Off p_offset;  //This member gives the offset from the start of the file at which the first byte of the segment resides.
  Elf32_Addr p_vaddr;  //This member gives the virtual address at which the first byte of the segment resides in memory.
  Elf32_Addr p_paddr;  //On systems for which physical addressing is relevant, this member is reserved for the segment's physical address. This member requires operating system specific information.
  Elf32_Word p_filesz; //This member gives the number of bytes in the file image of the segment; it may be zero.
  Elf32_Word p_memsz;  //This member gives the number of bytes in the memory image of the segment; it may be zero.
  Elf32_Word p_flags;  //This member gives flags relevant to the segment. Defined flag values are given in Figure 3-22, below.
  Elf32_Word p_align;  //Loadable process segments must have congruent values for p_vaddr and p_offset, modulo the page size. This member gives the value to which the segments are aligned in memory and in the file. Values 0 and 1 mean that no alignment is required. Otherwise, p_align should be a positive, integral power of 2, and p_vaddr should equal p_offset, modulo p_align.
} Elf32_Phdr;

//Defined program header flags
#define PF_X 1 //The segment may be executed.
#define PF_W 2 //The segment may be written to.
#define PF_R 4 //The segment may be read.
#define PF_MASKPROC 0xf0000000 //Reserved for processor-specific purposes (see 4.6, Program headers).

//Segment Types, p_type
#define PT_NULL    0 //The array element is unused; other members' values are undefined. This type lets the program header table have ignored entries.
#define PT_LOAD    1 //The array element specifies a loadable segment, described by p_filesz and p_memsz (for additional explanation, see PT_LOAD below).
#define PT_DYNAMIC 2 //The array element specifies dynamic linking information. See subsection 4.7.
#define PT_INTERP  3 //The array element specifies the location and size of a null-terminated path name to invoke as an interpreter.
#define PT_NOTE    4 //The array element specifies the location and size of auxiliary information.
#define PT_SHLIB   5 //This segment type is reserved but has unspecified semantics.
#define PT_PHDR    6 //The array element, if present, specifies the location and size of the program header table itself (for additional explanation, see PT_ PHDR below).
#define PT_LOPROC  0x70000000 //Values in this inclusive range are reserved for processor-specific semantics.
#define PT_HIPROC  0x7fffffff

//The dynamic section
typedef struct{
  Elf32_Sword d_tag;
  Elf32_Word d_val;
} Elf32_Dyn;

//Dynamic section tags
#define DT_NULL     0  //Ignored. This entry marks the end of the dynamic array. mandatory
#define DT_NEEDED   1  //Index in the string table of the name of a needed library. multiple
#define DT_PLTRELSZ 2  //These entries are unused by versions 1-2 of the ARM EABI. unused
#define DT_PLTGOT   3
#define DT_HASH     4  //The offset of the hash table section in the dynamic segment. mandatory
#define DT_STRTAB   5  //The offset of the string table section in the dynamic segment. mandatory
#define DT_SYMTAB   6  //The offset of the symbol table section in the dynamic segment. mandatory
#define DT_RELA     7  //The offset in the dynamic segment of an SHT_RELA relocation section, Its byte size, and the byte size of an ARM RELA-type relocation entry. optional
#define DT_RELASZ   8
#define DT_RELAENT  9
#define DT_STRSZ    10 //The byte size of the string table section. mandatory
#define DT_SYMENT   11 //The byte size of an ARM symbol table entryЧ16. mandatory
#define DT_INIT     12 //These entries are unused by versions 1-2 of the ARM EABI. unused
#define DT_FINI     13
#define DT_SONAME   14 //The Index in the string table of the name of this shared object. mandatory
#define DT_RPATH    15 //Unused by the ARM EABI. unused
#define DT_SYMBOLIC 16
#define DT_REL      17 //The offset in the dynamic segment of an SHT_REL relocation section, Its byte size, and the byte size of an ARM REL-type relocation entry optional
#define DT_RELSZ    18
#define DT_RELENT   19
#define DT_PLTREL   20 //These entries are unused by versions 1-2 of the ARM EABI. unused
#define DT_DEBUG    21
#define DT_TEXTREL  22
#define DT_JMPREL   23
#define DT_BIND_NOW 24
#define DT_LOPROC   0x70000000 //Values in this range are reserved to the ARM EABI. unused
#define DT_HIPROC   0x7fffffff

//Relocation Entries
typedef struct{
  Elf32_Addr r_offset;
  Elf32_Word r_info;
} Elf32_Rel;

typedef struct{
  Elf32_Addr  r_offset;
  Elf32_Word  r_info;
  Elf32_Sword r_addend;
} Elf32_Rela;

#define ELF32_R_SYM(i)    ((i)>>8)
#define ELF32_R_TYPE(i)   ((unsigned char)(i))
#define ELF32_R_INFO(s,t) (((s)<<8)+(unsigned char)(t))

//ARM relocation types
#define R_ARM_NONE            0   //Any No relocation. Encodes dependencies between sections.
#define R_ARM_PC24            1   //ARM B/BL S Ц P + A
#define R_ARM_ABS32           2   //32-bit word S + A
#define R_ARM_REL32           3   //32-bit word S Ц P + A
#define R_ARM_PC13            4   //ARM LDR r, [pc,Е] S Ц P + A
#define R_ARM_ABS16           5   //16-bit half-word S + A
#define R_ARM_ABS12           6   //ARM LDR/STR S + A
#define R_ARM_THM_ABS5        7   //Thumb LDR/STR S + A
#define R_ARM_ABS8            8   //8-bit byte S + A
#define R_ARM_SBREL32         9   //32-bit word S Ц B + A
#define R_ARM_THM_PC22        10  //Thumb BL pair S Ц P+ A
#define R_ARM_THM_PC8         11  //Thumb LDR r, [pc,Е] S Ц P + A
#define R_ARM_AMP_VCALL9      12  //AMP VCALL ObsoleteЧSA-1500 only.
#define R_ARM_SWI24           13  //ARM SWI S + A
#define R_ARM_THM_SWI8        14  //Thumb SWI S + A
#define R_ARM_XPC25           15  //ARM BLX S Ц P+ A
#define R_ARM_THM_XPC22       16  //Thumb BLX pair S Ц P+ A
#define R_ARM_COPY            20  //32 bit word Copy symbol at dynamic link time.
#define R_ARM_GLOB_DAT        21  //32 bit word Create GOT entry.
#define R_ARM_JUMP_SLOT       22  //32 bit word Create PLT entry.
#define R_ARM_RELATIVE        23  //32 bit word Adjust by program base.
#define R_ARM_GOTOFF          24  //32 bit word Offset relative to start of GOT.
#define R_ARM_GOTPC           25  //32 bit word Insert address of GOT.
#define R_ARM_GOT32           26  //32 bit word Entry in GOT.
#define R_ARM_PLT32           27  //ARM BL Entry in PLT.
#define R_ARM_ALU_PCREL_7_0   32  //ARM ADD/SUB (S Ц P + A) & 0x000000FF
#define R_ARM_ALU_PCREL_15_8  33  //ARM ADD/SUB (S Ц P + A) & 0x0000FF00
#define R_ARM_ALU_PCREL_23_15 34  //ARM ADD/SUB (S Ц P + A) & 0x00FF0000
#define R_ARM_LDR_SBREL_11_0  35  //ARM LDR/STR (S Ц B + A) & 0x00000FFF
#define R_ARM_ALU_SBREL_19_12 36  //ARM ADD/SUB (S Ц B + A) & 0x000FF000
#define R_ARM_ALU_SBREL_27_20 37  //ARM ADD/SUB (S Ц B + A) & 0x0FF00000
#define R_ARM_GNU_VTENTRY     100 //32 bit word Record C++ vtable entry.
#define R_ARM_GNU_VTINHERIT   101 //32 bit word Record C++ member usage.
#define R_ARM_THM_PC11        102 //Thumb B S Ц P + A
#define R_ARM_THM_PC9         103 //Thumb B<cond> S Ц P + A
#define R_ARM_RXPC25          249 //ARM BLX (?S Ц ?P) + A For calls between program segments.
#define R_ARM_RSBREL32        250 //Word (?S Ц ?SB) + A For an offset from SB, the static base.
#define R_ARM_THM_RPC22       251 //Thumb BL/BLX pair (?S Ц ?P) + A For calls between program segments.
#define R_ARM_RREL32          252 //Word (?S Ц ?P) + A For on offset between two segments.
#define R_ARM_RABS32          253 //Word ?S + A For the address of a location in the target segment.
#define R_ARM_RPC24           254 //ARM B/BL (?S Ц ?P) + A For calls between program segments.
#define R_ARM_RBASE           255 //None NoneЧIdentifies the segment being relocated by the following relocation directives.

typedef long TElfEntry(char *, void *,void *,void *);


/*   «агрузка формата 'ELF' в оперативную пам€ть и немедленное исполнение программной секции   */

//¬озвращаемые значени€:
//  0  - Ёльф запущен 
// -1  - Ќе открываетс€ эльф
// -2  - Ќе читаетс€ эльф
// -3  - ƒа и не эльф это вовсе (Ќет необходимого ID = 0x7F,'E','L','F')
// -4  - Ќе найден программный заголовок
// -5  - Ќе читаетс€ программный заголовок
// -6  - Ќе найден динамический сегмент
// -7  - Ќе выдел€етс€ пам€ть под динамический сегмент
// -8  - Ќе читаетс€ динамический сегмент
// -9  - —лишком много програмных сегментов
// -10 - Ќе читаетс€ программный сегмент
// -11 - Ќеизвестный тип программного сегмента
// -12 - Ќеизвестный тип релокации
// -13 - Ќе выдел€етьс€ пам€ть под эльф (Ќехватка свободной RAM)

long elfload(char *filename, void *param1, void *param2, void *param3);

#endif // __ELF_H__


