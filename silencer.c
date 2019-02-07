/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: goodspb.luo@gmail.com                                        |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_silencer.h"
#include "SAPI.h"

PHP_FUNCTION(slc_curl_init);
PHP_FUNCTION(slc_curl_setopt);
PHP_FUNCTION(slc_curl_exec);
PHP_FUNCTION(slc_curl_setopt_array);

ZEND_DECLARE_MODULE_GLOBALS(silencer)

/* Make sapi_module accessable */
extern sapi_module_struct sapi_module;

/* True global resources - no need for thread safety here */
static int le_silencer;

/* {{{ PHP_INI
 */
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("silencer.enable",      "1", PHP_INI_ALL, OnUpdateBool, enable, zend_silencer_globals, silencer_globals)
    STD_PHP_INI_ENTRY("silencer.enable_cli",  "1", PHP_INI_ALL, OnUpdateBool, enable_cli, zend_silencer_globals, silencer_globals)
PHP_INI_END()
/* }}} */

/* {{{ dependency */
static const zend_module_dep silencer_dependency[] = {
		ZEND_MOD_REQUIRED("standard")
		ZEND_MOD_REQUIRED("curl")
		ZEND_MOD_REQUIRED("json")
};
/* }}} */

/* {{{ php_silencer_init_globals
 */
static void php_silencer_init_globals(zend_silencer_globals *silencer_globals)
{

}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(silencer)
{
	ZEND_INIT_MODULE_GLOBALS(silencer, php_silencer_init_globals, NULL);
	REGISTER_INI_ENTRIES();

	if (!SIG(enable)) {
		return SUCCESS;
	}

	/* if env is cli */
	if (strncmp(sapi_module.name, "cli", sizeof("cli") -1) == 0 && !SIG(enable_cli)) {
		return SUCCESS;
    }

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(silencer)
{
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(silencer)
{
#if defined(COMPILE_DL_SILENCER) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(silencer)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(silencer)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "silencer support", "enabled");
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
/* }}} */

/* {{{ silencer_functions[]
 *
 * Every user visible function must have an entry in silencer_functions[].
 */
const zend_function_entry silencer_functions[] = {
	PHP_FE(slc_curl_init, NULL)
	PHP_FE(slc_curl_setopt, NULL)
	PHP_FE(slc_curl_setopt_array, NULL)
	PHP_FE(slc_curl_exec, NULL)
	PHP_FE_END	/* Must be the last line in silencer_functions[] */
};
/* }}} */

PHP_FUNCTION(slc_curl_init)
{

}

PHP_FUNCTION(slc_curl_setopt)
{

}

PHP_FUNCTION(slc_curl_setopt_array)
{

}

PHP_FUNCTION(slc_curl_exec)
{

}

/* {{{ silencer_module_entry
 */
zend_module_entry silencer_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	silencer_dependency,
	"silencer",
	silencer_functions,
	PHP_MINIT(silencer),
	PHP_MSHUTDOWN(silencer),
	PHP_RINIT(silencer),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(silencer),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(silencer),
	PHP_SILENCER_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_SILENCER
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(silencer)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
