#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section(__versions) = {
	{ 0xfece093d, "module_layout" },
	{ 0xfe990052, "gpio_free" },
	{ 0xab7e65c2, "class_unregister" },
	{ 0xe8be6d2f, "device_destroy" },
	{ 0xd003e9c3, "class_destroy" },
	{ 0x82a137a5, "device_create" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x9b09fde, "__class_create" },
	{ 0x52fc0849, "__register_chrdev" },
	{ 0x5f754e5a, "memset" },
	{ 0x51a910c0, "arm_copy_to_user" },
	{ 0x46d59da3, "gpiod_get_raw_value" },
	{ 0xd1915fde, "gpiod_set_raw_value" },
	{ 0x2724c21b, "gpiod_direction_output_raw" },
	{ 0x455de5e3, "gpio_to_desc" },
	{ 0x47229b5c, "gpio_request" },
	{ 0xae353d77, "arm_copy_from_user" },
	{ 0xeae2c290, "try_module_get" },
	{ 0xa7e36f1a, "module_put" },
	{ 0xc5850110, "printk" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "4D5A6070E90774F3E5CBFEA");
