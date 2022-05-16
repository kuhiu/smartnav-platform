#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xfb080ece, "module_layout" },
	{ 0x8a8062bf, "platform_driver_unregister" },
	{ 0xc8afcc70, "device_destroy" },
	{ 0x38e4b428, "__platform_driver_register" },
	{ 0x3e6badd6, "class_destroy" },
	{ 0xe9e59beb, "device_create" },
	{ 0xd1f18866, "cdev_del" },
	{ 0x2d0d89b2, "__class_create" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xb9757c96, "cdev_add" },
	{ 0xfad496fc, "cdev_init" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xf99fc839, "kmalloc_caches" },
	{ 0x92f552c6, "kmem_cache_alloc" },
	{ 0x3dcf1ffa, "__wake_up" },
	{ 0x822137e2, "arm_heavy_mb" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0xdb7305a1, "__stack_chk_fail" },
	{ 0xf4fa543b, "arm_copy_to_user" },
	{ 0x49970de8, "finish_wait" },
	{ 0x1000e51, "schedule" },
	{ 0x647af474, "prepare_to_wait_event" },
	{ 0xfe487975, "init_wait_entry" },
	{ 0x37a0cba, "kfree" },
	{ 0xd6b8e852, "request_threaded_irq" },
	{ 0x7ae7907a, "platform_get_irq" },
	{ 0xe97c4103, "ioremap" },
	{ 0xae9849dd, "__request_region" },
	{ 0x3143af08, "platform_get_resource" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xc94d8e3b, "iomem_resource" },
	{ 0x4384eb42, "__release_region" },
	{ 0xedc03953, "iounmap" },
	{ 0xc1514a3b, "free_irq" },
	{ 0x7c32d0f0, "printk" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

