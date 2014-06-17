Xtreeme
=======

C++ semantic database, developed between 2010 and 2012 and updated a bit in 2014.

Example
-------

	% ./buildAll
	% export LD_LIBRARY_PATH=./lib
	% ./bin/xconsole
	@prefix owl: <http://www.w3.org/2002/07/owl#> .
	INSERT DATA {
		GRAPH <g> {
			<isIn> a owl:TransitiveProperty.
			<Warsaw> <isIn> <Poland>.
			<Poland> <isIn> <Europe>.
		}
	};
	SELECT *;

With the given data, it will infer that:

	<Warsaw> <isIn> <Europe>.
