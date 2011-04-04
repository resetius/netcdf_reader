#ifndef NETCDF_CMD_H
#define NETCDF_CMD_H

#include <set>
#include <string>
#include <string.h>
#include <stdio.h>
#include <netcdf.hh>

struct Slice {
	NcDim * dim;
	std::string dim_name;
	int dim_num;
	int from;
	int total;

	Slice(NcFile * f, const char * d, int f1, int t1) : dim(0),
       		dim_name(d), 
		dim_num(0), from(f1), total(t1) 
	{
		dim = f->get_dim(d);
		if (!dim) {
			fprintf(stderr, "dimention %s not found\n", d);
		}

		long size = dim->size();
		if (from == -1) from = 0;
		if (from >= size) from = size - 1;

		if (total == -1) total = size;
		if (total > size) total = size;
	}
};

inline bool operator < (const Slice & s1, const Slice & s2) 
{
	return s1.dim_name < s2.dim_name;
}

struct CMD_Parser {
	int cur_;
	int argc_;
	char ** argv_;
	NcFile * f_;
	typedef std::set < Slice > slices_t;
	slices_t slices_;
	bool text_;

	CMD_Parser (int argc, char * argv[]): f_(0), cur_(1), argc_(argc), argv_(argv), text_(false) {}
	~CMD_Parser() { delete f_; }

	void parse();
	void open(const char * name);
	int next();

	void help();
	void info();

	void info_var(int number);
	void info_var(const char * name);
	void info_var(NcVar *);

	void info_att(int number);
	void info_att(const char * name);
	void info_att(NcAtt *);

	void check_file();

	void text_mode() { text_ = true; }
	void dump(const char * to, const char * what);
	void add_slice(const char * dim);
	void add_slice(const char * dim, double from, double to);
	void reset_slice();
};

int yyparse(CMD_Parser * );

#endif /* NETCDF_CMD_H */

