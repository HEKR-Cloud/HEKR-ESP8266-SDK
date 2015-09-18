#ifndef __IOTSS_H__
#define __IOTSS_H__

/* Platform related */
#if defined(IOTSS_PLATFORM_ESP) && defined(__GNUC__)
#define FUNC_MODIFIER __attribute__((section(".irom0.text")))
#else
#define FUNC_MODIFIER 
#endif

enum iotss_native_proc_arg_type
{
	IOTSS_NATIVE_PROC_ARG_TYPE_UNKNOWN = 0,
	IOTSS_NATIVE_PROC_ARG_TYPE_NIL,
	IOTSS_NATIVE_PROC_ARG_TYPE_VOID,
	IOTSS_NATIVE_PROC_ARG_TYPE_INT,
	IOTSS_NATIVE_PROC_ARG_TYPE_BOOL,
	IOTSS_NATIVE_PROC_ARG_TYPE_STR,
	IOTSS_NATIVE_PROC_ARG_TYPE_SYM,
	IOTSS_NATIVE_PROC_ARG_TYPE_RAW,
	IOTSS_NATIVE_PROC_ARG_TYPE_PROC,
	IOTSS_NATIVE_PROC_ARG_TYPE_EVENT,
	IOTSS_NATIVE_PROC_ARG_TYPE_LISTENER,
	IOTSS_NATIVE_PROC_ARG_TYPE_ERR,
	IOTSS_NATIVE_PROC_ARG_TYPE_OBJ,
};
typedef enum iotss_native_proc_arg_type iotss_native_proc_arg_type_t;

/*struct iotss*/
struct iotss_vm;
typedef struct iotss_vm iotss_vm_t;
struct iotss_native_proc_args;
typedef struct iotss_native_proc_arg iotss_native_proc_args_t;

extern struct iotss_vm *g_vm;

struct iotss_static_bindings_item
{
	char *name;
	void(*callback)(iotss_native_proc_args_t *args);
	uint8_t args_min;
	uint8_t args_max;
	char *type_sig;
	size_t len;
	uint8_t checksum;
};
typedef struct iotss_static_bindings_item iotss_static_bindings_item_t;

/* Boolean */
#ifndef __cplusplus 
typedef enum
{
	iotss_false = 0,
	iotss_true = 1,
} iotss_bool;
#else
typedef enum
{
	iotss_false = false,
	iotss_true = true,
} iotss_bool;
#endif

typedef struct iotss_native_proc_arg
{
	iotss_native_proc_arg_type_t type;
	union
	{
		/* nil and void doesn't required extra space */
		int value_int;
		iotss_bool value_bool;
		struct
		{
			char *str;
			size_t len;
		} value_str, value_sym, value_err;
		struct
		{
			void *ptr;
			void(*mark)(struct iotss_vm *vm, void *ptr);
			void(*sweep)(void *ptr);
		} value_raw;
		void *value_proc;
		void *value_event;
		void *value_listener;

		/* Not recommended */
		void *value_obj;
	} u;
	struct iotss_native_proc_arg *next;
	struct iotss_native_proc_arg *prev;
} iotss_native_proc_arg_t;

extern int FUNC_MODIFIER iotss_vm_bind_static_bindings_from_items(iotss_vm_t *vm, const char *name, iotss_static_bindings_item_t *items);
extern void FUNC_MODIFIER iotss_native_proc_arg_destroy(iotss_native_proc_arg_t *arg);
extern iotss_native_proc_arg_t *FUNC_MODIFIER iotss_native_proc_args_get_arg(iotss_native_proc_args_t *args);

/* Macro for initialize an item */
#define IOTSS_STATIC_BINDINGS_ITEM(name, cb, args_min, args_max, type_sig) \
{name, cb, args_min, args_max, type_sig, 0, 0}
#define IOTSS_STATIC_BINDINGS_ITEM_FINAL \
{NULL, NULL, 0, 0, 0, 0, 0}

#endif