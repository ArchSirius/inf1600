.global func_s

func_s:
	flds b
	flds c
	fmulp
	fstps a
	flds f
	flds c
	faddp
	flds a
	fdivp
	fstps a
	flds g
	flds d
	fsubrp
	flds e
	fdivrp
	flds a
	fmulp
	fstps a
	flds g
	flds d
	fsubrp
	flds e
	fmulp
	flds a
	faddp
	fstps a
	
	
	ret
