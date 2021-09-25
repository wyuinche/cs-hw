#include "sfp.h"
#define NAN_NUM 31745
#define bias 15
#include <stdio.h>

float pow(int a, int b){
	if (b != 0)
		return (float)a * pow(a, b-1);
	else
		return 1;
}

sfp int2sfp(int input){
	int sign = 0, exp, frac;
	int E;
	int bit_arr_te[32] = { 0, };
	int bit_len = 1;
	int num = input;

	if (input < 0){
		sign = 1;
		num *= -1;
	}
	
	if (input == 0)
		return 0;

	for (int i = 0; i < 32; i++) {
		bit_arr_te[i] = num % 2;
		num /= 2;
		if (num != 0)
			bit_len++;
	}

	E = bit_len - 1;
	exp = E + bias;

	frac = 0;
	if(E >= 10)
		for(int i = 0; i < 10; i++)
			frac+= bit_arr_te[E-1-i]*pow(2, 9-i);
	else
		for(int i = 0; i < E; i++)
			frac += bit_arr_te[E-1-i]*pow(2, 9-i);

	if (exp > 30) {
		if (sign == 0)
			return pow(2, 15) - pow(2, 10);
		else
			return pow(2, 16) - pow(2, 10);
	}

	sign = sign << 15;
	exp = exp << 10;

	return frac + exp + sign;
}

int sfp2int(sfp input){
	int bit_arr_te[16];
	int bit_arr_de[16];
	int frac_bit[10];
	int sign, exp, frac;
	int nancheck = 0;
	int E;
	sfp insfp = input;

	if(input == 0)
		return 0;
	else if(input == 31745)
		return (-1)*(2147483648);
	else if(input == 31744)
		return 2147483647;
	else if(input == 64512)
		return (-1)*2147483648;
	
	for (int i = 0; i < 16; i++) {
		bit_arr_te[i] = insfp % 2;
		insfp /= 2;
	}

	for (int i = 0; i < 16; i++)
		bit_arr_de[i] = bit_arr_te[15 - i];

	if (bit_arr_de[0] == 1)
		sign = -1;
	else
		sign = 1;

	exp = 0;
	for (int i = 1; i < 6; i++)
		exp += bit_arr_de[i] * pow(2, 5 - i);
	for (int i = 0; i < 10; i++)
		frac_bit[i] = bit_arr_de[i + 6];

	for (int i = 0; i < 10; i++)
		nancheck += frac_bit[i];

	if (exp > 30)
		if (nancheck == 0)
			if (sign == 1)
				return 2147483647;
			else
				return (-1)*2147483648;
		else
			return (-1)*2147483648;

	E = exp - bias;

	if (E > 10) {
		frac = 0;
		for (int i = 0; i < 10; i++)
			frac += frac_bit[i] * pow(2, E - 1 - i);
	}
	else {
		frac = 0;
		for (int i = 0; i < E; i++)
			frac += frac_bit[i] * pow(2, E - 1 - i);
	}

	return sign * (frac + pow(2, E));
}

sfp float2sfp(float input){
	int sign = 0, exp, frac;
	int bit_arr[200] = {0,};
	int E;
	int front;
	float back;
	int front_len = 0;
	int back_pos, back_len = 1;
	int frac_pos = 0;

	if (input == 0)
		return 0;

	if (input < 0)
	{
		sign = 1;
		front = input;
		front *= -1;
		back = (-1)*input -(float)front;
	}
	else
	{
		sign = 0;
		front = input;
		back = input - (float)front;
	}

	front_len = 0;
	if (front != 0) {
		while (1) {
			bit_arr[front_len] = front % 2;
			front /= 2;
			front_len++;
			if (front == 0)
				break;
		}
	}

	if ((front_len != 0)&&(front_len != 1))
		for (int i = 0; i < front_len/2; i++) {
            		int tmp = bit_arr[i];
            		bit_arr[i] = bit_arr[front_len-1-i];
            		bit_arr[front_len-1-i] = tmp;
		}

	back_pos = front_len;
	back_len = 0;
	while (1) {
        	back_len++;
		if ((back -1/pow(2,back_len)) >= 0.0)
		{
			bit_arr[back_pos] = 1;
			back -= 1/pow(2, back_len);
		}
		else
			bit_arr[back_pos] = 0;
		back_pos++;

		if (back == 0)
			break;
		if (back_pos == 199)
			break;
	}

	if (front_len == 0) {
		E = -1;
		for (int i = 0; i < 200; i++)
			if (bit_arr[i] == 0)
				E--;
			else
				break;
	}
	else
		E = front_len - 1;

	exp = E + bias;

	if (exp < 0)
		return 0;
	else if (exp > 30) {
        for(int i = 1; i < 11; i++){
            if(bit_arr[i] == 1)
                if(bit_arr[0] == 0)
                    return NAN_NUM;
                else
                    return NAN_NUM + pow(2, 15);
        }
		if (sign == 0)
			return pow(2, 15) - pow(2, 10);
		else
			return pow(2, 16) - pow(2, 10);
	}

	if(E >= 0){
        for(frac_pos = 0; frac_pos < 200; frac_pos++){
            if(bit_arr[frac_pos] == 1)
                break;
        }
        frac_pos++;
        frac = 0;
        for(int i = frac_pos; i < frac_pos+10; i++)
            frac += bit_arr[i]*pow(2, 9+frac_pos -i);

	}
	else{
        int epos = E*(-1);
        frac = 0;
        for(int i = epos; i < epos+10; i++)
            frac += bit_arr[i]*pow(2, 9+epos -i);
	}

    exp = exp*pow(2, 10);
    sign = sign*pow(2, 15);

	return frac + exp + sign;
}

float sfp2float(sfp input){
	int bit_arr[16];
	sfp insfp = input;
    	float sign;
    	int exp = 0;
    	int frac = 0;
    	int E;
    	float out;

    	if(input == 0)
        	return 0;
    	else if(input == pow(2, 15))
        	return 0;
	else if(input == 31744)
		return pow(2, 128);
	else if(input == 64512)
		return (-1)*pow(2, 128);
	else if((input>= 31745)&&(input <= 32767))
		return 0/0;
	else if((input >= 64513)&&(input <= 65535))
		return 0/0;

	for(int i = 15; i >=0; i--){
        	bit_arr[i] = insfp%2;
        	insfp /= 2;
	}

    	if(bit_arr[0] ==0)
        	sign = 1;
    	else if(bit_arr[0] == 1)
        	sign = -1;

	for(int i = 1; i < 6; i++)
        	exp += bit_arr[i]*pow(2, 5-i);
    	for(int i = 6; i < 16; i++)
        	frac += bit_arr[i]*pow(2, 15-i);

    	if(exp > 30)
        	if(frac != 0)
            		return 0/0;
        	else
    	    		if(sign == 1)
                		return 340282366920938463463374607431768211456.0;
            		else
                		return -340282366920938463463374607431768211456.0;

    	E = exp - bias;

    	out = 0;

    	if(E > 0){
        	for(int i = 6; i < E+6; i++)
            		out += bit_arr[i]*pow(2, E+5-i);
            	out += pow(2, E);
        	for(int i = E+6; i < 16; i++)
            		out += bit_arr[i]*(1/pow(2, (i-(E+5))));
    	}
    	else if(E == 0){
        	for(int i = 6; i < 16; i++){
            		out += bit_arr[i]*(1/pow(2, i-5));
        	}
        	out += pow(2, 0);
	}
    	else{
        	for(int i = 6; i < 16; i++){
            	out += bit_arr[i]*1/pow(2, i-E-5);
       	 	}
        	out += 1/pow(2, -E);
    	}

    	return out*sign;
}

sfp sfp_add(sfp a, sfp b){
    	int inf_a = 0, inf_b = 0;
    	int sign_a, exp_a;
    	int sign_b, exp_b;
    	int frac_a, frac_b;
    	int bit_a[16] = {0,};
   	int bit_b[16] ={0,};
    	int sign_o = 0, exp_o = 0, frac_o = 0;
    	int shift = 0;
	int* round_arr = (int*)malloc(sizeof(int));
	int frac_bc = 0;	
	
	if ((a == 0) && (b == 0))
		return 0;
	else if ((a == 0) && (b != 0))
		return b;
	else if ((a != 0) && (b == 0))
		return a;

    	for(int i = 0; i < 16; i++){
        	bit_a[15-i] = a%2;
        	a /=2;
    	}
    	sign_a = bit_a[0];

    	for(int i = 0; i < 16; i++){
        	bit_b[15-i] = b%2;
        	b /=2;
    	}
    	sign_b = bit_b[0];

    	exp_a = 0;
    	for(int i = 1; i < 6; i++)
        	exp_a += bit_a[i]*pow(2, 5-i);
    	exp_b = 0;
    	for(int i = 1; i < 6; i++)
        	exp_b += bit_b[i]*pow(2, 5-i);

    	frac_a = 0;
    	for(int i = 6; i<16; i++)
        	frac_a += bit_a[i]*pow(2,15-i);
    	frac_b = 0;
    	for(int i =6; i<16; i++)
        	frac_b += bit_b[i]*pow(2,15-i);

    	if(exp_a > 30)
        	if(frac_a != 0)
            		inf_a = 2;
        	else
            		if(bit_a[0]==0)
                		inf_a = 1;
            		else
                		inf_a = -1;
    	if(exp_b > 30)
        	if(frac_b != 0)
            		inf_b = 2;
        	else
            		if(bit_b[0]==0)
                		inf_b = 1;
            		else
                		inf_b = -1;

    	if((inf_a != 0)||(inf_b !=0))
    	{
        	if((inf_a ==1)&&(inf_b==1)){
            		sign_o = 0;
            		frac_o = 0;
            		exp_o = 31;
        	}
        	else if((inf_a*inf_b) == -1){
            		sign_o = 0;
            		frac_o = 1;
            		exp_o = 31;
        	}
        	else if(((inf_a == 1)&&(inf_b ==0))||((inf_a == 0)&&(inf_b == 1))){
            		sign_o = 0;
            		frac_o = 0;
            		exp_o = 31;
        	}
        	else if((inf_a == -1)&&(inf_b==-1)){
            		sign_o = 1;
            		frac_o = 0;
            		exp_o = 31;
        	}
        	else if(((inf_a == -1)&&(inf_b == 0))||((inf_a ==0)&&(inf_b = -1))){
            		sign_o = 1;
            		frac_o = 0;
            		exp_o = 31;
        	}
        	else if((inf_a ==2)||(inf_b==2)){
            		sign_o = 0;
            		frac_o = 1;
            		exp_o = 31;
        	}

        	sign_o = sign_o <<15;
        	exp_o = exp_o <<10;
        	return sign_o+exp_o+frac_o;
    	}

    	if(exp_b > exp_a){
        	int tmp;
        	tmp = sign_a;
        	sign_a = sign_b;
        	sign_b = tmp;
        	tmp = exp_a;
        	exp_a = exp_b;
        	exp_b = tmp;
        	tmp = frac_a;
        	frac_a = frac_b;
        	frac_b = tmp;
        	for(int i = 0; i < 16; i++){
            		int imp;
            		imp = bit_a[i];
            		bit_a[i] = bit_b[i];
            		bit_b[i] = bit_a[i];
        	}
    	}

    	shift = exp_a - exp_b;
    	exp_b = exp_a;

	if (shift == 0) {
		if (exp_a == 30)
		{
			sfp c = a + b;
			int ca[16] = { 0, };
			int nancheck = 0;

			for (int i = 0; i < 16; i++)
			{
				ca[15 - i] = c % 2;
				c /= 2;
			}
			for (int i = 6; i < 16; i++)
				if (ca[i] != 0)
					return NAN_NUM;
			if (ca[0] == 0)
				return NAN_NUM - 1;
			else
				return NAN_NUM - 1 + pow(2, 15);
			
		}
		exp_o = ++exp_a;
		sign_o = sign_a;
		frac_o = (frac_a + frac_b) / 2;
		
		exp_o = exp_o * pow(2, 10);
		sign_o = sign_o * pow(2, 15);
		return exp_o + sign_o + frac_o;
	}
	else
		frac_b += pow(2, 10);

	round_arr = (int*)realloc(round_arr, sizeof(int)*shift);
	
	frac_bc = frac_b;
	for (int i = 0; i < shift; i++) {
		round_arr[i] = frac_bc % 2;
		frac_bc /= 2;
	}
	frac_b = (float)frac_b / pow(2, shift);
    	
	if((sign_a == 0)&&(sign_b == 0)){
        	frac_o = frac_a+frac_b;
        	exp_o = exp_a;
        	sign_o = 0;
		if (round_arr[shift - 1] == 1)
			frac_o++;
		if(frac_o/pow(2, 10) >= 1){
			exp_o++;
			frac_o %= (int)pow(2, 10);
		}
    	}
    	else if((sign_a == 1)&&(sign_b == 1)){
        	frac_o = frac_a+frac_b;
        	exp_o = exp_a;
        	sign_o = 1;
		if (round_arr[shift - 1] == 1)
			frac_o++;
    		if(frac_o/pow(2, 10) >= 1)
		{
			exp_o++;
			frac_o %= (int)pow(2,10);
	
		}
	}
	else if((sign_a == 1)&&(sign_b == 0)){
        	if(frac_a >= frac_b){
            		frac_o = frac_a - frac_b;
            	exp_o = exp_a;
            	sign_o = 1;
			if (round_arr[shift - 1] == 1)
				frac_o += 1;
        	}
        	else{
            		frac_a += pow(2, 10);
            		frac_o = frac_a - frac_b;

            		if(frac_o/pow(2, 10) == 1){
				frac_o %= (int)pow(2, 10);
                	exp_o = exp_a;
                	sign_o = 1;
            		}
            		else{
                		int shift_exp = 1;
                		while(1){
                    			if(frac_o/pow(2,10-shift_exp)==1)
                        			break;
                    			else
                        			shift_exp++;
                    		}
                		frac_o = frac_o *pow(2, shift_exp);
                		exp_o -= shift_exp;
                		sign_o = 1;
            		}
			if (round_arr[shift - 1] == 1)
				frac_o += 1;
        	}
    	}
    	else{
        	if(frac_a >= frac_b){
            		frac_o = frac_a - frac_b;
            		exp_o = exp_a;
            		sign_o = 0;
			if (round_arr[shift - 1] == 1)
				frac_o += 1;
        	}
        	else{
            		frac_a += pow(2,10);
            		frac_o = frac_a - frac_b;

            		if(frac_o/pow(2, 10) == 1){
				frac_o %= (int)pow(2, 10);
                		exp_o = exp_a;
                		sign_o = 0;
            		}
            		else{
                		int shift_exp = 1;
                		while(1){
                    		if(frac_o/pow(2, 10-shift_exp) ==1)
                        		break;
                    		else
                        		shift_exp++;
                    		}
                		frac_o = frac_o*pow(2, shift_exp);
                		exp_o -= shift_exp;
                		sign_o = 0;
            		}
				if (round_arr[shift - 1] == 1)
					frac_o += 1;
        	}
    	}
	
    	exp_o = exp_o*pow(2, 10);
    	sign_o = sign_o*pow(2, 15);

    	return exp_o + sign_o + frac_o;
}



char* sfp2bits(sfp result){
	char* bit_rep = (char*)malloc(sizeof(char) * 17);
	for (int i = 15; i > -1; i--) {
		if(result % 2 == 0)
            bit_rep[i] = '0';
        else
            bit_rep[i] = '1';
		result /= 2;
    }

	bit_rep[16] = '\0';

	return bit_rep;
}
