/* test_string_utils.cpp
 * =====================
 * Created by: WTJW
 * Created on: 23/05/2007
 */

#include <iostream>
#include <string>
#include <string_utils.h>		// Mine

using namespace std;
using namespace string_utils;

int main(int argc, char **argv) {
//	ERROR<int, double> dammit;
	
	string a("apple"), b("APPle"), c("pear");
	
	// is_equal_case_insensitive()
	cerr << "a = <" << a << ">\n";		//DEBUG
	cerr << "b = <" << b << ">\n";		//DEBUG
	cerr << "c = <" << c << ">\n";		//DEBUG
	cerr << "(a == b) = <" << (a == b) << ">\n";		//DEBUG
	cerr << "is_equal_case_insensitive(a, b) = <" << is_equal_case_insensitive(a, b) << ">\n";		//DEBUG
	cerr << "(a == c) = <" << (a == c) << ">\n";		//DEBUG
	cerr << "is_equal_case_insensitive(a, c) = <" << is_equal_case_insensitive(a, c) << ">\n";		//DEBUG
	cerr << "is_equal_case_insensitive(a, \"aPPLe\") = <" << is_equal_case_insensitive(a, "aPPLe") << ">\n";		//DEBUG
	cerr << "is_equal_case_insensitive(a, \"baNANa\") = <" << is_equal_case_insensitive(a, "baNANa") << ">\n";		//DEBUG
	cerr << "is_equal_case_insensitive(\"AppLE\", a) = <" << is_equal_case_insensitive("AppLE", a) << ">\n";		//DEBUG
	cerr << "is_equal_case_insensitive(\"foonly\", \"FoOnLy\") = <" << is_equal_case_insensitive("foonly", "FoOnLy") << ">\n";		//DEBUG
	cerr << "is_equal_case_insensitive(\"not\", \"same\") = <" << is_equal_case_insensitive("not", "same") << ">\n";		//DEBUG
	cerr << "is_equal_case_insensitive(\"different\", a) = <" << is_equal_case_insensitive("different", a) << ">\n";		//DEBUG
	
	// starts_with(), ends_with()
	cerr << "starts_with(a, \"\") = <" << starts_with(a, "") << ">\n";		//DEBUG
	cerr << "starts_with(a, a) = <" << starts_with(a, a) << ">\n";		//DEBUG
	cerr << "starts_with(a, \"foo\") = <" << starts_with(a, "foo") << ">\n";		//DEBUG
	cerr << "starts_with(a, \"app\") = <" << starts_with(a, "app") << ">\n";		//DEBUG
	cerr << "starts_with(a, \"footoolong\") = <" << starts_with(a, "footoolong") << ">\n";		//DEBUG
	cerr << "starts_with(a, \"appletoolong\") = <" << starts_with(a, "appletoolong") << ">\n";		//DEBUG
	cerr << "ends_with(a, \"\") = <" << ends_with(a, "") << ">\n";		//DEBUG
	cerr << "ends_with(a, a) = <" << ends_with(a, a) << ">\n";		//DEBUG
	cerr << "ends_with(a, \"foo\") = <" << ends_with(a, "foo") << ">\n";		//DEBUG
	cerr << "ends_with(a, \"ple\") = <" << ends_with(a, "ple") << ">\n";		//DEBUG
	cerr << "ends_with(a, \"toolongapple\") = <" << ends_with(a, "toolongapple") << ">\n";		//DEBUG
	
	// Both arguments are strings
	cerr << "starts_with(a, b) = <" << starts_with(a, b) << ">\n";		//DEBUG
	
	// Both arguments are C strings
	cerr << "starts_with(\"blah\", \"no\") = <" << starts_with("blah", "no") << ">\n";		//DEBUG
	cerr << "starts_with(\"foonly\", \"foo\") = <" << starts_with("foonly", "foo") << ">\n";		//DEBUG
	
	// First arg is a C string
	cerr << "starts_with(\"apples are good for your health\", a) = <" << starts_with("apples are good for your health", a) << ">\n";		//DEBUG
	cerr << "starts_with(\"this does not start with pear\", c) = <" << starts_with("this does not start with pear", c) << ">\n";		//DEBUG
	
//	// Should cause a compiler error
//	cerr << "starts_with(a, 42.69) = <" << starts_with(a, 42.69) << ">\n";		//DEBUG
	
	// replace_first(), replace_all()
	bool bool_result;
	int int_result;
	
	bool_result = replace_first(a, 'p', 'x');
	cerr << "a after replace_first(a, 'p', 'x') = <" << a << ">\n";		//DEBUG
	cerr << "bool_result = <" << bool_result << ">\n";		//DEBUG
	
	// Replacing with longer strings
	bool_result = replace_first(a, "x", "XXX");
	cerr << "a after replace_first(a, \"x\", \"XXX\") = <" << a << ">\n";		//DEBUG
	cerr << "bool_result = <" << bool_result << ">\n";		//DEBUG
	
	bool_result = replace_first(a, "p", "YYYYY");
	cerr << "a after replace_first(a, \"p\", \"YYYYY\") = <" << a << ">\n";		//DEBUG
	cerr << "bool_result = <" << bool_result << ">\n";		//DEBUG
	
	bool_result = replace_first(a, "qqq", "ERROR");			// Should not find anything
	cerr << "a after replace_first(a, \"q\", \"ERROR\") = <" << a << ">\n";		//DEBUG
	cerr << "bool_result = <" << bool_result << ">\n";		//DEBUG
	
	bool_result = replace_first(a, string("e"), "123");
	cerr << "a after replace_first(a, string(\"e\"), \"123\") = <" << a << ">\n";		//DEBUG
	
	// Deleting strings
	int_result = replace_all(a, "XX");
	cerr << "a after replace_all(a, \"XX\") = <" << a << ">\n";		//DEBUG
	cerr << "int_result = <" << int_result << ">\n";		//DEBUG
	
	// Don't find the to_find string in a just-replaced part of the string
	int_result = replace_all(a, "YY", "YYY");		// Should be 7 "Y"s afterwards
	cerr << "a after replace_all(a, \"YY\", \"YYY\") = <" << a << ">\n";		//DEBUG
	
	// Single characters
	int_result = replace_all(a, 'Y', 'Z');
	cerr << "a after replace_all(a, 'Y', 'Z') = <" << a << ">\n";		//DEBUG
	cerr << "int_result = <" << int_result << ">\n";		//DEBUG
	
	// Replacing with shorter strings
	int_result = replace_all(a, "ZZZ", "X");
	cerr << "a after replace_all(a, \"ZZZ\", \"X\") = <" << a << ">\n";		//DEBUG
	cerr << "int_result = <" << int_result << ">\n";		//DEBUG
	
	return 0;
}
