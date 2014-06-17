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

With the given data, it will infer that:

	<Warsaw> <isIn> <Europe>.

You can see it with:

	SELECT * WHERE { <Warsaw> <isIn> ?what };
	:: Query sent.
	| what |
	| (23)Poland |
	| (28)Europe |
	--------

Or you can select everything, including the metadata about the reasoning process:

	SELECT *;
	:: Query sent.
	| ID | S | P | O | C |
	| (5)"isIn type TransitiveProperty g"^^Statement | (1)isIn | (2)type | (3)TransitiveProperty | (4)g |
	| (20)"\"isIn type TransitiveProperty g\"^^Statement source \"{8ff98a45-c4e0-4436-9032-9cbb01f77dd5}\" metagraph"^^Statement | (5)"isIn type TransitiveProperty g"^^Statement | (16)source | (19)"{8ff98a45-c4e0-4436-9032-9cbb01f77dd5}" | (15)metagraph |
	| (21)"\"{8ff98a45-c4e0-4436-9032-9cbb01f77dd5}\" type Insertion metagraph"^^Statement | (19)"{8ff98a45-c4e0-4436-9032-9cbb01f77dd5}" | (2)type | (17)Insertion | (15)metagraph |
	| (24)"Warsaw isIn Poland g"^^Statement | (22)Warsaw | (1)isIn | (23)Poland | (4)g |
	| (26)"\"Warsaw isIn Poland g\"^^Statement source \"{869b3207-9832-4347-a35c-2f2a0e30e1f5}\" metagraph"^^Statement | (24)"Warsaw isIn Poland g"^^Statement | (16)source | (25)"{869b3207-9832-4347-a35c-2f2a0e30e1f5}" | (15)metagraph |
	| (27)"\"{869b3207-9832-4347-a35c-2f2a0e30e1f5}\" type Insertion metagraph"^^Statement | (25)"{869b3207-9832-4347-a35c-2f2a0e30e1f5}" | (2)type | (17)Insertion | (15)metagraph |
	| (29)"Poland isIn Europe g"^^Statement | (23)Poland | (1)isIn | (28)Europe | (4)g |
	| (33)"\"Poland isIn Europe g\"^^Statement source \"{a1de19f9-32cc-4259-ba2a-e5ea2f91e127}\" metagraph"^^Statement | (29)"Poland isIn Europe g"^^Statement | (16)source | (30)"{a1de19f9-32cc-4259-ba2a-e5ea2f91e127}" | (15)metagraph |
	| (34)"\"{a1de19f9-32cc-4259-ba2a-e5ea2f91e127}\" type Insertion metagraph"^^Statement | (30)"{a1de19f9-32cc-4259-ba2a-e5ea2f91e127}" | (2)type | (17)Insertion | (15)metagraph |
	| (35)"\"Warsaw isIn Europe metagraph\"^^Statement source \"{3f6eaffc-4770-48d2-8491-e86d0185675a}\" metagraph"^^Statement | (31)"Warsaw isIn Europe metagraph"^^Statement | (16)source | (32)"{3f6eaffc-4770-48d2-8491-e86d0185675a}" | (15)metagraph |
	| (36)"\"{3f6eaffc-4770-48d2-8491-e86d0185675a}\" type Inference metagraph"^^Statement | (32)"{3f6eaffc-4770-48d2-8491-e86d0185675a}" | (2)type | (18)Inference | (15)metagraph |
	| (37)"\"{3f6eaffc-4770-48d2-8491-e86d0185675a}\" source \"Poland isIn Europe g\"^^Statement metagraph"^^Statement | (32)"{3f6eaffc-4770-48d2-8491-e86d0185675a}" | (16)source | (29)"Poland isIn Europe g"^^Statement | (15)metagraph |
	| (38)"\"{3f6eaffc-4770-48d2-8491-e86d0185675a}\" source \"isIn type TransitiveProperty g\"^^Statement metagraph"^^Statement | (32)"{3f6eaffc-4770-48d2-8491-e86d0185675a}" | (16)source | (5)"isIn type TransitiveProperty g"^^Statement | (15)metagraph |
	| (39)"\"{3f6eaffc-4770-48d2-8491-e86d0185675a}\" source \"Warsaw isIn Poland g\"^^Statement metagraph"^^Statement | (32)"{3f6eaffc-4770-48d2-8491-e86d0185675a}" | (16)source | (24)"Warsaw isIn Poland g"^^Statement | (15)metagraph |
	| (31)"Warsaw isIn Europe metagraph"^^Statement | (22)Warsaw | (1)isIn | (28)Europe | (15)metagraph |
	----------------------
