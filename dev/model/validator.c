
/*
  +------------------------------------------------------------------------+
  | Phalcon Framework                                                      |
  +------------------------------------------------------------------------+
  | Copyright (c) 2011-2012 Phalcon Team (http://www.phalconphp.com)       |
  +------------------------------------------------------------------------+
  | This source file is subject to the New BSD License that is bundled     |
  | with this package in the file docs/LICENSE.txt.                        |
  |                                                                        |
  | If you did not receive a copy of the license and are unable to         |
  | obtain it through the world-wide-web, please send an email             |
  | to license@phalconphp.com so we can send you a copy immediately.       |
  +------------------------------------------------------------------------+
  | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
  |          Eduar Carvajal <eduar@phalconphp.com>                         |
  +------------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_phalcon.h"
#include "phalcon.h"

#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/require.h"
#include "kernel/object.h"
#include "kernel/debug.h"
#include "kernel/assert.h"
#include "kernel/array.h"
#include "kernel/operators.h"
#include "kernel/memory.h"

#include "zend_operators.h"
#include "zend_exceptions.h"
#include "zend_interfaces.h"

/**
 * Phalcon_Model_Validator constructor
 *
 * @param Phalcon_Model_Base $record
 * @param string $field
 * @param string $value
 * @param array $options
 */
PHP_METHOD(Phalcon_Model_Validator, __construct){

	zval *record = NULL, *field_name = NULL, *value = NULL, *options = NULL;
	zval *a0 = NULL, *a1 = NULL, *a2 = NULL;

	PHALCON_MM_GROW();
	
	PHALCON_INIT_VAR(a0);
	array_init(a0);
	zend_update_property(phalcon_model_validator_ce, this_ptr, "_options", strlen("_options"), a0 TSRMLS_CC);
	
	PHALCON_INIT_VAR(a1);
	array_init(a1);
	zend_update_property(phalcon_model_validator_ce, this_ptr, "_messages", strlen("_messages"), a1 TSRMLS_CC);
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zzz|z", &record, &field_name, &value, &options) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (!options) {
		
		PHALCON_INIT_VAR(a2);
		array_init(a2);
		PHALCON_CPY_WRT(options, a2);
	}
	
	phalcon_update_property_zval(this_ptr, "_record", strlen("_record"), record TSRMLS_CC);
	phalcon_update_property_zval(this_ptr, "_fieldName", strlen("_fieldName"), field_name TSRMLS_CC);
	phalcon_update_property_zval(this_ptr, "_value", strlen("_value"), value TSRMLS_CC);
	phalcon_update_property_zval(this_ptr, "_options", strlen("_options"), options TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Appends a message to the validator
 *
 * @param string $message
 * @param string $field
 * @param string $type
 */
PHP_METHOD(Phalcon_Model_Validator, appendMessage){

	zval *message = NULL, *field = NULL, *type = NULL;
	zval *t0 = NULL, *t1 = NULL;
	zval *r0 = NULL, *r1 = NULL;
	zval *c0 = NULL, *c1 = NULL;
	zval *i0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|zz", &message, &field, &type) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (!field) {
		
		PHALCON_INIT_VAR(field);
		ZVAL_NULL(field);
	} else {
		PHALCON_SEPARATE_PARAM(field);
	}
	
	if (!type) {
		
		PHALCON_INIT_VAR(type);
		ZVAL_NULL(type);
	} else {
		PHALCON_SEPARATE_PARAM(type);
	}
	
	if (!zend_is_true(field)) {
		PHALCON_ALLOC_ZVAL_MM(t0);
		phalcon_read_property(&t0, this_ptr, "_fieldName", sizeof("_fieldName")-1, PHALCON_NOISY TSRMLS_CC);
		PHALCON_CPY_WRT(field, t0);
	}
	if (!zend_is_true(type)) {
		PHALCON_ALLOC_ZVAL_MM(r0);
		PHALCON_INIT_VAR(c0);
		ZVAL_STRING(c0, "Validator", 1);
		PHALCON_INIT_VAR(c1);
		ZVAL_STRING(c1, "", 1);
		PHALCON_ALLOC_ZVAL_MM(r1);
		phalcon_get_class(r1, this_ptr TSRMLS_CC);
		PHALCON_CALL_FUNC_PARAMS_3(r0, "str_replace", c0, c1, r1, 0x003);
		PHALCON_CPY_WRT(type, r0);
	}
	
	
	PHALCON_ALLOC_ZVAL_MM(i0);
	object_init_ex(i0, phalcon_model_message_ce);
	PHALCON_CALL_METHOD_PARAMS_3_NORETURN(i0, "__construct", message, field, type, PHALCON_CHECK);
	
	PHALCON_ALLOC_ZVAL_MM(t1);
	phalcon_read_property(&t1, this_ptr, "_messages", sizeof("_messages")-1, PHALCON_NOISY TSRMLS_CC);
	phalcon_array_append(&t1, i0, PHALCON_NO_SEPARATE_THX TSRMLS_CC);
	phalcon_update_property_zval(this_ptr, "_messages", strlen("_messages"), t1 TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Returns messages generated by the validator
 *
 * @return array
 */
PHP_METHOD(Phalcon_Model_Validator, getMessages){

	zval *t0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(t0);
	phalcon_read_property(&t0, this_ptr, "_messages", sizeof("_messages")-1, PHALCON_NOISY TSRMLS_CC);
	
	PHALCON_RETURN_CHECK_CTOR(t0);
}

/**
 * Check whether option "required" has been passed as option
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Model_Validator, isRequired){

	zval *required = NULL;
	zval *t0 = NULL, *t1 = NULL, *t2 = NULL, *t3 = NULL, *t4 = NULL, *t5 = NULL;
	zval *r0 = NULL, *r1 = NULL, *r2 = NULL, *r3 = NULL;
	int eval_int;

	PHALCON_MM_GROW();
	PHALCON_INIT_VAR(required);
	ZVAL_BOOL(required, 1);
	
	PHALCON_ALLOC_ZVAL_MM(t0);
	phalcon_read_property(&t0, this_ptr, "_value", sizeof("_value")-1, PHALCON_NOISY TSRMLS_CC);
	
	PHALCON_INIT_VAR(t1);
	ZVAL_STRING(t1, "", 1);
	
	PHALCON_INIT_VAR(r0);
	is_identical_function(r0, t1, t0 TSRMLS_CC);
	
	PHALCON_ALLOC_ZVAL_MM(t2);
	phalcon_read_property(&t2, this_ptr, "_value", sizeof("_value")-1, PHALCON_NOISY TSRMLS_CC);
	
	PHALCON_INIT_VAR(t3);
	ZVAL_NULL(t3);
	
	PHALCON_INIT_VAR(r1);
	is_identical_function(r1, t3, t2 TSRMLS_CC);
	
	PHALCON_INIT_VAR(r2);
	ZVAL_BOOL(r2, zend_is_true(r0) || zend_is_true(r1));
	if (zend_is_true(r2)) {
		PHALCON_ALLOC_ZVAL_MM(t4);
		phalcon_read_property(&t4, this_ptr, "_options", sizeof("_options")-1, PHALCON_NOISY TSRMLS_CC);
		eval_int = phalcon_array_isset_string(t4, "required", strlen("required")+1);
		if (eval_int) {
			PHALCON_ALLOC_ZVAL_MM(t5);
			phalcon_read_property(&t5, this_ptr, "_options", sizeof("_options")-1, PHALCON_NOISY TSRMLS_CC);
			PHALCON_ALLOC_ZVAL_MM(r3);
			phalcon_array_fetch_string(&r3, t5, "required", strlen("required"), PHALCON_NOISY TSRMLS_CC);
			PHALCON_CPY_WRT(required, r3);
		}
		
		PHALCON_RETURN_CHECK_CTOR(required);
	} else {
		PHALCON_MM_RESTORE();
		RETURN_TRUE;
	}
	
	PHALCON_MM_RESTORE();
}

/**
 * Returns all the options from the validator
 *
 * @return array
 */
PHP_METHOD(Phalcon_Model_Validator, getOptions){

	zval *t0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(t0);
	phalcon_read_property(&t0, this_ptr, "_options", sizeof("_options")-1, PHALCON_NOISY TSRMLS_CC);
	
	PHALCON_RETURN_CHECK_CTOR(t0);
}

/**
 * Returns an option
 *
 * @param string $option
 * @return mixed
 */
PHP_METHOD(Phalcon_Model_Validator, getOption){

	zval *option = NULL;
	zval *r0 = NULL, *r1 = NULL, *r2 = NULL;
	zval *t0 = NULL, *t1 = NULL, *t2 = NULL;
	int eval_int;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &option) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_ALLOC_ZVAL_MM(t0);
	phalcon_read_property(&t0, this_ptr, "_options", sizeof("_options")-1, PHALCON_NOISY TSRMLS_CC);
	eval_int = phalcon_array_isset(t0, option);
	PHALCON_INIT_VAR(r1);
	ZVAL_BOOL(r1, eval_int);
	if (zend_is_true(r1)) {
		PHALCON_ALLOC_ZVAL_MM(t1);
		phalcon_read_property(&t1, this_ptr, "_options", sizeof("_options")-1, PHALCON_NOISY TSRMLS_CC);
		PHALCON_ALLOC_ZVAL_MM(r2);
		phalcon_array_fetch(&r2, t1, option, PHALCON_NOISY TSRMLS_CC);
		r0 = r2;
	} else {
		PHALCON_INIT_VAR(t2);
		ZVAL_STRING(t2, "", 1);
		r0 = t2;
	}
	
	PHALCON_RETURN_CHECK_CTOR(r0);
}

/**
 * Check whether a option has been defined in the validator options
 *
 * @param string $option
 * @return boolean
 */
PHP_METHOD(Phalcon_Model_Validator, isSetOption){

	zval *option = NULL;
	zval *t0 = NULL;
	zval *r0 = NULL;
	int eval_int;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &option) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_ALLOC_ZVAL_MM(t0);
	phalcon_read_property(&t0, this_ptr, "_options", sizeof("_options")-1, PHALCON_NOISY TSRMLS_CC);
	eval_int = phalcon_array_isset(t0, option);
	PHALCON_INIT_VAR(r0);
	ZVAL_BOOL(r0, eval_int);
	
	PHALCON_RETURN_NCTOR(r0);
}

/**
 * Returns the value of the validated field
 *
 * @return mixed
 */
PHP_METHOD(Phalcon_Model_Validator, getValue){

	zval *t0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(t0);
	phalcon_read_property(&t0, this_ptr, "_value", sizeof("_value")-1, PHALCON_NOISY TSRMLS_CC);
	
	PHALCON_RETURN_CHECK_CTOR(t0);
}

/**
 * Devuelve el nombre del campo validado
 *
 * @access protected
 * @return string
 */
PHP_METHOD(Phalcon_Model_Validator, getFieldName){

	zval *t0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(t0);
	phalcon_read_property(&t0, this_ptr, "_fieldName", sizeof("_fieldName")-1, PHALCON_NOISY TSRMLS_CC);
	
	PHALCON_RETURN_CHECK_CTOR(t0);
}

/**
 * Returns Phalcon_Model_Base related record
 *
 * @return ActiveRecord
 */
PHP_METHOD(Phalcon_Model_Validator, getRecord){

	zval *t0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(t0);
	phalcon_read_property(&t0, this_ptr, "_record", sizeof("_record")-1, PHALCON_NOISY TSRMLS_CC);
	
	PHALCON_RETURN_CHECK_CTOR(t0);
}

/**
 * This method can be overridden to implement specific option validations for the validator
 *
 */
PHP_METHOD(Phalcon_Model_Validator, checkOptions){


	
}

