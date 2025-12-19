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



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xd272d446, "__fentry__" },
	{ 0x09390960, "add" },
	{ 0x09390960, "sub" },
	{ 0x09390960, "mul" },
	{ 0x09390960, "divi" },
	{ 0x09390960, "avg" },
	{ 0x1b3db703, "param_ops_int" },
	{ 0xe8213e80, "_printk" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0x70eca2ca, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0xd272d446,
	0x09390960,
	0x09390960,
	0x09390960,
	0x09390960,
	0x09390960,
	0x1b3db703,
	0xe8213e80,
	0xd272d446,
	0x70eca2ca,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"__fentry__\0"
	"add\0"
	"sub\0"
	"mul\0"
	"divi\0"
	"avg\0"
	"param_ops_int\0"
	"_printk\0"
	"__x86_return_thunk\0"
	"module_layout\0"
;

MODULE_INFO(depends, "math");


MODULE_INFO(srcversion, "A2A62C66631D11C46A1C755");
