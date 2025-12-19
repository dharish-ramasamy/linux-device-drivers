#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

KSYMTAB_FUNC(add, "", "");
KSYMTAB_FUNC(sub, "", "");
KSYMTAB_FUNC(mul, "", "");
KSYMTAB_FUNC(divi, "", "");
KSYMTAB_FUNC(avg, "", "");

SYMBOL_CRC(add, 0x09390960, "");
SYMBOL_CRC(sub, 0x09390960, "");
SYMBOL_CRC(mul, 0x09390960, "");
SYMBOL_CRC(divi, 0x09390960, "");
SYMBOL_CRC(avg, 0x09390960, "");

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xd272d446, "__fentry__" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0xe8213e80, "_printk" },
	{ 0xbebe66ff, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0xd272d446,
	0xd272d446,
	0xe8213e80,
	0xbebe66ff,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"__fentry__\0"
	"__x86_return_thunk\0"
	"_printk\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "A0F14E3C4282430F736C9B4");
