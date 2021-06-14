# DIGITAL_SIGNATURES_NIST-PQC_ROUND3_BENCHMARKS

This repository contains the benchmarks of the 3rd. Round NIST's Post Quantum Crypto Contest of Digital Signatures in Process of Standardization (CRYSTALS-DILITHIUM, FALCON, RAINBOW) and the Alternative Candidates (GeMSS, PICNIC, SPHINCS+)

This project is finished, the main purpose was to measure the "Signature" and "Verification" in clock cycles of all versions of the 3rd. round implementations of digital signatures in the PQC Contest and the alternative candidates, here you can download the modified versions of the schemes and test it yourself.

All of the schemes offers the reference implementation, this are the "standard" versions of every one of them, some of them offers the optimized versions and the alternative versions, because there is no ground basis of what every one of them has to accomplish, some offer in the optimized versions "C optimized code" of their schemes, others offers the "AVX2", "SSE4" and "NEON" optimized versions, in other schemes this is true in the alternative versions, that is why in this repository in the "reference" folder you will find the "standard" versions of the schemes and in the "optimized" folder you will find the "AVX2" versions of the schemes, the "C optimized code", "SSE4" and "NEON" are not included in this repository, so in the down tables the version column that starts with "ref" and "opt" are making reference to the "standard" version and the "AVX2" version respectively.

I am not the owner of the sourcecode contained in the original schemes, the codes belongs to the original developers of the schemes, I only developed the file that contains the main function (benchmarks.c), also modified another files in the algorithms to execute the code the most similar way in all the schemes, the "benchmarks.c" file is include in all implementations of the schemes, next you will find the instructions to execute them:

1. Download this repository and extract the content, in the main folder create a folder named RESULTS.

2. In order to execute the benchmarks in all the schemes you will have to follow the instructions of installation of the individual schemes, the mayority of the schemes only need "OpenSSL", "GCC" and "MAKE", the GeMMS Signature needs the Keccak package installed locally on your computer. Here is the link to download the original schemes: https://csrc.nist.gov/projects/post-quantum-cryptography/round-3-submissions

3. In the main of this repository you will find 5 shell scripts to automate the operations; MAKES.sh performs a make command in every implementation in order to compile the codes, RUNS.sh performs the benchmarks of every implementation and writes the results in the RESULTS folder, CLEANS.sh performs a make clean command in order to reverse what the make command does, CYCLES.sh modify the number of executing cycles of every implementation from 100 to whatever number you like of iterations, since some schemes take up to more than 7 seconds to execute each process it will take up to 12 hours to execute every scheme 100 iterations, that is why I recomend to keep the number of iterations to 100 times, finally the MICRO.sh modify in every benchmarks.c file the speed of the processor of the computer that will perform the test process, this is in the order of gigahertz, you will have to modify the code and write down the correct speed of your processor, when I ran the tests my computer was 1895000000 hz of raw speed, the test must be performed with an Intel(R) processor from the Haswell(TM) architecture or more recent, it has to have the AVX2 instruction set, the TurboBoost(TM) technology and the HyperThreading(TM) technology disabled.

This software is distributed on an "AS IS" basis WITHOUT WARRANTY OF ANY KIND."

The original software implementations belongs to the RESPECTIVE OWNERS.

If you have any questions, recomendations or corrections regarding this repository feel free to contact me to: jose.rodriguez@cimat.mx

The machine where I performed the original test has the following characteristics:
- Intel(R) Core(TM) i5-4300U CPU @ 1.90GHz, 1895Mhz
- 4GB of RAM DDR3, 3824MiB
- SSD 128GB Sata3

Next I include a table with the results of measuring the digital signature algorithms; it includes the three 3rd. Round Candidates of the NIST's Post Quantum Crypto Contest also the Alternative Candidates, all signatures were tested 100 cycles and averaging; the categories where 3rd. round candidates signature, 3rd. round candidates verification, alternative candidates signature and alternative candidates verification, the results are in the clasifications mentions above sorted by the fastest signature and verification accordingly in every category.





**3rd. Round Candidates Signature**
|	**SIGNATURE NAME**	|	**VERSION**	|	**SECRET SIZE KEY BITS**	|	**PUBLIC SIZE KEY BITS**	|	**SIGN CLOCK CYCLES**	|	**SIGN TIME SECONDS**	|	**VERIFY CLOCK CYCLES**	|	**VERIFY TIME SECONDS**	|
|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|
|	CRYSTALS-DILITHIUM	|	 opt-dilithium2	|	sk-2544-bytes	|	pk-1312-bytes	|	154108	|	 0.000081	|	108431	|	 0.000057	|
|	CRYSTALS-DILITHIUM	|	 opt-dilithium3-AES-R	|	sk-4016-bytes	|	pk-1952-bytes	|	198148	|	 0.000105	|	106613	|	 0.000056	|
|	CRYSTALS-DILITHIUM	|	 opt-dilithium2-AES-R	|	sk-2544-bytes	|	pk-1312-bytes	|	211633	|	 0.000112	|	76147	|	 0.000040	|
|	RAINBOW	|	 ref-Ia-Circumzenithal	|	sk-101200-bytes	|	pk-58800-bytes	|	226756	|	 0.000120	|	2930841	|	 0.001547	|
|	RAINBOW	|	 ref-Ia-Classic	|	sk-101200-bytes	|	pk-157800-bytes	|	232357	|	 0.000123	|	33981	|	 0.000018	|
|	RAINBOW	|	 opt-Ia-Circumzenithal	|	sk-101200-bytes	|	pk-58800-bytes	|	290261	|	 0.000153	|	2973740	|	 0.001569	|
|	RAINBOW	|	 opt-Ia-Classic	|	sk-101200-bytes	|	pk-157800-bytes	|	292396	|	 0.000154	|	39257	|	 0.000021	|
|	CRYSTALS-DILITHIUM	|	 opt-dilithium5	|	sk-4880-bytes	|	pk-2592-bytes	|	358765	|	 0.000189	|	276552	|	 0.000146	|
|	CRYSTALS-DILITHIUM	|	 opt-dilithium3-AES-R	|	sk-4016-bytes	|	pk-1952-bytes	|	363608	|	 0.000192	|	106990	|	 0.000056	|
|	CRYSTALS-DILITHIUM	|	 opt-dilithium2-R	|	sk-2544-bytes	|	pk-1312-bytes	|	427615	|	 0.000226	|	108628	|	 0.000057	|
|	CRYSTALS-DILITHIUM	|	 opt-dilithium5-AES	|	sk-4880-bytes	|	pk-2592-bytes	|	442229	|	 0.000233	|	160114	|	 0.000084	|
|	CRYSTALS-DILITHIUM	|	 opt-dilithium3	|	sk-4016-bytes	|	pk-1952-bytes	|	533572	|	 0.000282	|	173986	|	 0.000092	|
|	CRYSTALS-DILITHIUM	|	 opt-dilithium5-AES-R	|	sk-4880-bytes	|	pk-2592-bytes	|	574838	|	 0.000303	|	165358	|	 0.000087	|
|	CRYSTALS-DILITHIUM	|	 ref-dilithium2	|	sk-2544-bytes	|	pk-1312-bytes	|	631261	|	 0.000333	|	349102	|	 0.000184	|
|	CRYSTALS-DILITHIUM	|	 opt-dilithium3-R	|	sk-4016-bytes	|	pk-1952-bytes	|	656512	|	 0.000346	|	174079	|	 0.000092	|
|	CRYSTALS-DILITHIUM	|	 opt-dilithium5-R	|	sk-4880-bytes	|	pk-2592-bytes	|	755641	|	 0.000399	|	273948	|	 0.000145	|
|	CRYSTALS-DILITHIUM	|	 opt-dilithium2-AES	|	sk-2544-bytes	|	pk-1312-bytes	|	863498	|	 0.000456	|	75926	|	 0.000040	|
|	FALCON	|	 opt-512avx2	|	sk-1281-bytes	|	pk-897-bytes	|	872461	|	 0.000460	|	142907	|	 0.000075	|
|	FALCON	|	 opt-512fpu	|	sk-1281-bytes	|	pk-897-bytes	|	1150796	|	 0.000607	|	127902	|	 0.000067	|
|	CRYSTALS-DILITHIUM	|	 ref-dilithium5	|	sk-4880-bytes	|	pk-2592-bytes	|	1424899	|	 0.000752	|	907139	|	 0.000479	|
|	RAINBOW	|	 opt-IIIc-Circumzenithal	|	sk-611300-bytes	|	pk-258400-bytes	|	1488527	|	 0.000786	|	17662756	|	 0.009321	|
|	RAINBOW	|	 opt-IIIc-Classic	|	sk-611300-bytes	|	pk-861400-bytes	|	1497667	|	 0.000790	|	241188	|	 0.000127	|
|	CRYSTALS-DILITHIUM	|	 ref-dilithium2-AES-R	|	sk-2544-bytes	|	pk-1312-bytes	|	1593431	|	 0.000841	|	638951	|	 0.000337	|
|	RAINBOW	|	 ref-IIIc-Classic	|	sk-611300-bytes	|	pk-861400-bytes	|	1669924	|	 0.000881	|	174075	|	 0.000092	|
|	RAINBOW	|	 ref-IIIc-Circumzenithal	|	sk-611300-bytes	|	pk-258400-bytes	|	1678350	|	 0.000886	|	17661329	|	 0.009320	|
|	FALCON	|	 opt-1024avx2	|	sk-2305-bytes	|	pk-1793-bytes	|	1778357	|	 0.000938	|	298568	|	 0.000158	|
|	CRYSTALS-DILITHIUM	|	 ref-dilithium3-AES	|	sk-4016-bytes	|	pk-1952-bytes	|	1941873	|	 0.001025	|	1098991	|	 0.000580	|
|	CRYSTALS-DILITHIUM	|	 ref-dilithium2-R	|	sk-2544-bytes	|	pk-1312-bytes	|	1990440	|	 0.001050	|	346571	|	 0.000183	|
|	FALCON	|	 opt-1024fpu	|	sk-2305-bytes	|	pk-1793-bytes	|	2323713	|	 0.001226	|	271727	|	 0.000143	|
|	CRYSTALS-DILITHIUM	|	 ref-dilithium3	|	sk-4016-bytes	|	pk-1952-bytes	|	2442644	|	 0.001289	|	557890	|	 0.000294	|
|	RAINBOW	|	 opt-Vc-Circumzenithal	|	sk-1375700-bytes	|	pk-523600-bytes	|	2514242	|	 0.001327	|	39868305	|	 0.021039	|
|	RAINBOW	|	 opt-Vc-Classic	|	sk-1375700-bytes	|	pk-1885400-bytes	|	2531558	|	 0.001336	|	447632	|	 0.000236	|
|	CRYSTALS-DILITHIUM	|	 ref-dilithium3	|	sk-4016-bytes	|	pk-1952-bytes	|	3233412	|	 0.001706	|	561836	|	 0.000296	|
|	CRYSTALS-DILITHIUM	|	 ref-dilithium3-AES-R	|	sk-4016-bytes	|	pk-1952-bytes	|	3344577	|	 0.001765	|	1106818	|	 0.000584	|
|	RAINBOW	|	 ref-Vc-Circumzenithal	|	sk-1375700-bytes	|	pk-523600-bytes	|	3530717	|	 0.001863	|	40201672	|	 0.021215	|
|	CRYSTALS-DILITHIUM	|	 ref-dilithium5-R	|	sk-4880-bytes	|	pk-2592-bytes	|	3590951	|	 0.001895	|	904290	|	 0.000477	|
|	CRYSTALS-DILITHIUM	|	 ref-dilithium5-AES	|	sk-4880-bytes	|	pk-2592-bytes	|	4339643	|	 0.002290	|	1950357	|	 0.001029	|
|	CRYSTALS-DILITHIUM	|	 ref-dilithium5-AES-R	|	sk-4880-bytes	|	pk-2592-bytes	|	5479102	|	 0.002891	|	1941471	|	 0.001025	|
|	RAINBOW	|	 ref-Vc-Classic	|	sk-1375700-bytes	|	pk-1885400-bytes	|	5639776	|	 0.002976	|	645818	|	 0.000341	|
|	CRYSTALS-DILITHIUM	|	 ref-dilithium2-AES	|	sk-2544-bytes	|	pk-1312-bytes	|	6384250	|	 0.003369	|	639175	|	 0.000337	|
|	RAINBOW	|	 ref-Ia-Compressed	|	sk-60-bytes	|	pk-58800-bytes	|	11508326	|	 0.006073	|	2965928	|	 0.001565	|
|	FALCON	|	 ref-512	|	sk-1281-bytes	|	pk-897-bytes	|	15434756	|	 0.008145	|	127655	|	 0.000067	|
|	RAINBOW	|	 opt-Ia-Compressed	|	sk-60-bytes	|	pk-58800-bytes	|	18642629	|	 0.009838	|	2963065	|	 0.001564	|
|	FALCON	|	 ref-1024	|	sk-2305-bytes	|	pk-1793-bytes	|	33801613	|	 0.017837	|	270484	|	 0.000143	|
|	RAINBOW	|	 ref-IIIc-Compressed	|	sk-60-bytes	|	pk-258400-bytes	|	125814932	|	 0.066393	|	17641825	|	 0.009310	|
|	RAINBOW	|	 opt-IIIc-Compressed	|	sk-60-bytes	|	pk-258400-bytes	|	133113175	|	 0.070244	|	17694044	|	 0.009337	|
|	RAINBOW	|	 opt-Vc-Compressed	|	sk-60-bytes	|	pk-523600-bytes	|	237678445	|	 0.125424	|	39963676	|	 0.021089	|
|	RAINBOW	|	 ref-Vc-Compressed	|	sk-60-bytes	|	pk-523600-bytes	|	352857933	|	 0.186205	|	41302142	|	 0.021795	|


**3rd. Round Candidates Verification**
|	**SIGNATURE NAME**	|	**VERSION**	|	**SECRET SIZE KEY BITS**	|	**PUBLIC SIZE KEY BITS**	|	**SIGN CLOCK CYCLES**	|	**SIGN TIME SECONDS**	|	**VERIFY CLOCK CYCLES**	|	**VERIFY TIME SECONDS**	|
|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|
|	RAINBOW	|	 ref-Ia-Classic	|	sk-101200-bytes	|	pk-157800-bytes	|	232357	|	 0.000123	|	33981	|	 0.000018	|
|	RAINBOW	|	 opt-Ia-Classic	|	sk-101200-bytes	|	pk-157800-bytes	|	292396	|	 0.000154	|	39257	|	 0.000021	|
|	CRYSTALS-DILITHIUM	|	 opt-dilithium2-AES	|	sk-2544-bytes	|	pk-1312-bytes	|	863498	|	 0.000456	|	75926	|	 0.000040	|
|	CRYSTALS-DILITHIUM	|	 opt-dilithium2-AES-R	|	sk-2544-bytes	|	pk-1312-bytes	|	211633	|	 0.000112	|	76147	|	 0.000040	|
|	CRYSTALS-DILITHIUM	|	 opt-dilithium3-AES-R	|	sk-4016-bytes	|	pk-1952-bytes	|	198148	|	 0.000105	|	106613	|	 0.000056	|
|	CRYSTALS-DILITHIUM	|	 opt-dilithium3-AES-R	|	sk-4016-bytes	|	pk-1952-bytes	|	363608	|	 0.000192	|	106990	|	 0.000056	|
|	CRYSTALS-DILITHIUM	|	 opt-dilithium2	|	sk-2544-bytes	|	pk-1312-bytes	|	154108	|	 0.000081	|	108431	|	 0.000057	|
|	CRYSTALS-DILITHIUM	|	 opt-dilithium2-R	|	sk-2544-bytes	|	pk-1312-bytes	|	427615	|	 0.000226	|	108628	|	 0.000057	|
|	FALCON	|	 ref-512	|	sk-1281-bytes	|	pk-897-bytes	|	15434756	|	 0.008145	|	127655	|	 0.000067	|
|	FALCON	|	 opt-512fpu	|	sk-1281-bytes	|	pk-897-bytes	|	1150796	|	 0.000607	|	127902	|	 0.000067	|
|	FALCON	|	 opt-512avx2	|	sk-1281-bytes	|	pk-897-bytes	|	872461	|	 0.000460	|	142907	|	 0.000075	|
|	CRYSTALS-DILITHIUM	|	 opt-dilithium5-AES	|	sk-4880-bytes	|	pk-2592-bytes	|	442229	|	 0.000233	|	160114	|	 0.000084	|
|	CRYSTALS-DILITHIUM	|	 opt-dilithium5-AES-R	|	sk-4880-bytes	|	pk-2592-bytes	|	574838	|	 0.000303	|	165358	|	 0.000087	|
|	CRYSTALS-DILITHIUM	|	 opt-dilithium3	|	sk-4016-bytes	|	pk-1952-bytes	|	533572	|	 0.000282	|	173986	|	 0.000092	|
|	RAINBOW	|	 ref-IIIc-Classic	|	sk-611300-bytes	|	pk-861400-bytes	|	1669924	|	 0.000881	|	174075	|	 0.000092	|
|	CRYSTALS-DILITHIUM	|	 opt-dilithium3-R	|	sk-4016-bytes	|	pk-1952-bytes	|	656512	|	 0.000346	|	174079	|	 0.000092	|
|	RAINBOW	|	 opt-IIIc-Classic	|	sk-611300-bytes	|	pk-861400-bytes	|	1497667	|	 0.000790	|	241188	|	 0.000127	|
|	FALCON	|	 ref-1024	|	sk-2305-bytes	|	pk-1793-bytes	|	33801613	|	 0.017837	|	270484	|	 0.000143	|
|	FALCON	|	 opt-1024fpu	|	sk-2305-bytes	|	pk-1793-bytes	|	2323713	|	 0.001226	|	271727	|	 0.000143	|
|	CRYSTALS-DILITHIUM	|	 opt-dilithium5-R	|	sk-4880-bytes	|	pk-2592-bytes	|	755641	|	 0.000399	|	273948	|	 0.000145	|
|	CRYSTALS-DILITHIUM	|	 opt-dilithium5	|	sk-4880-bytes	|	pk-2592-bytes	|	358765	|	 0.000189	|	276552	|	 0.000146	|
|	FALCON	|	 opt-1024avx2	|	sk-2305-bytes	|	pk-1793-bytes	|	1778357	|	 0.000938	|	298568	|	 0.000158	|
|	CRYSTALS-DILITHIUM	|	 ref-dilithium2-R	|	sk-2544-bytes	|	pk-1312-bytes	|	1990440	|	 0.001050	|	346571	|	 0.000183	|
|	CRYSTALS-DILITHIUM	|	 ref-dilithium2	|	sk-2544-bytes	|	pk-1312-bytes	|	631261	|	 0.000333	|	349102	|	 0.000184	|
|	RAINBOW	|	 opt-Vc-Classic	|	sk-1375700-bytes	|	pk-1885400-bytes	|	2531558	|	 0.001336	|	447632	|	 0.000236	|
|	CRYSTALS-DILITHIUM	|	 ref-dilithium3	|	sk-4016-bytes	|	pk-1952-bytes	|	2442644	|	 0.001289	|	557890	|	 0.000294	|
|	CRYSTALS-DILITHIUM	|	 ref-dilithium3	|	sk-4016-bytes	|	pk-1952-bytes	|	3233412	|	 0.001706	|	561836	|	 0.000296	|
|	CRYSTALS-DILITHIUM	|	 ref-dilithium2-AES-R	|	sk-2544-bytes	|	pk-1312-bytes	|	1593431	|	 0.000841	|	638951	|	 0.000337	|
|	CRYSTALS-DILITHIUM	|	 ref-dilithium2-AES	|	sk-2544-bytes	|	pk-1312-bytes	|	6384250	|	 0.003369	|	639175	|	 0.000337	|
|	RAINBOW	|	 ref-Vc-Classic	|	sk-1375700-bytes	|	pk-1885400-bytes	|	5639776	|	 0.002976	|	645818	|	 0.000341	|
|	CRYSTALS-DILITHIUM	|	 ref-dilithium5-R	|	sk-4880-bytes	|	pk-2592-bytes	|	3590951	|	 0.001895	|	904290	|	 0.000477	|
|	CRYSTALS-DILITHIUM	|	 ref-dilithium5	|	sk-4880-bytes	|	pk-2592-bytes	|	1424899	|	 0.000752	|	907139	|	 0.000479	|
|	CRYSTALS-DILITHIUM	|	 ref-dilithium3-AES	|	sk-4016-bytes	|	pk-1952-bytes	|	1941873	|	 0.001025	|	1098991	|	 0.000580	|
|	CRYSTALS-DILITHIUM	|	 ref-dilithium3-AES-R	|	sk-4016-bytes	|	pk-1952-bytes	|	3344577	|	 0.001765	|	1106818	|	 0.000584	|
|	CRYSTALS-DILITHIUM	|	 ref-dilithium5-AES-R	|	sk-4880-bytes	|	pk-2592-bytes	|	5479102	|	 0.002891	|	1941471	|	 0.001025	|
|	CRYSTALS-DILITHIUM	|	 ref-dilithium5-AES	|	sk-4880-bytes	|	pk-2592-bytes	|	4339643	|	 0.002290	|	1950357	|	 0.001029	|
|	RAINBOW	|	 ref-Ia-Circumzenithal	|	sk-101200-bytes	|	pk-58800-bytes	|	226756	|	 0.000120	|	2930841	|	 0.001547	|
|	RAINBOW	|	 opt-Ia-Compressed	|	sk-60-bytes	|	pk-58800-bytes	|	18642629	|	 0.009838	|	2963065	|	 0.001564	|
|	RAINBOW	|	 ref-Ia-Compressed	|	sk-60-bytes	|	pk-58800-bytes	|	11508326	|	 0.006073	|	2965928	|	 0.001565	|
|	RAINBOW	|	 opt-Ia-Circumzenithal	|	sk-101200-bytes	|	pk-58800-bytes	|	290261	|	 0.000153	|	2973740	|	 0.001569	|
|	RAINBOW	|	 ref-IIIc-Compressed	|	sk-60-bytes	|	pk-258400-bytes	|	125814932	|	 0.066393	|	17641825	|	 0.009310	|
|	RAINBOW	|	 ref-IIIc-Circumzenithal	|	sk-611300-bytes	|	pk-258400-bytes	|	1678350	|	 0.000886	|	17661329	|	 0.009320	|
|	RAINBOW	|	 opt-IIIc-Circumzenithal	|	sk-611300-bytes	|	pk-258400-bytes	|	1488527	|	 0.000786	|	17662756	|	 0.009321	|
|	RAINBOW	|	 opt-IIIc-Compressed	|	sk-60-bytes	|	pk-258400-bytes	|	133113175	|	 0.070244	|	17694044	|	 0.009337	|
|	RAINBOW	|	 opt-Vc-Circumzenithal	|	sk-1375700-bytes	|	pk-523600-bytes	|	2514242	|	 0.001327	|	39868305	|	 0.021039	|
|	RAINBOW	|	 opt-Vc-Compressed	|	sk-60-bytes	|	pk-523600-bytes	|	237678445	|	 0.125424	|	39963676	|	 0.021089	|
|	RAINBOW	|	 ref-Vc-Circumzenithal	|	sk-1375700-bytes	|	pk-523600-bytes	|	3530717	|	 0.001863	|	40201672	|	 0.021215	|
|	RAINBOW	|	 ref-Vc-Compressed	|	sk-60-bytes		|	pk-523600-bytes	|      352857933|	 0.186205	|	41302142	|	 0.021795	|


**Alternative Candidates Signature**
|	**SIGNATURE NAME**	|	**VERSION**	|	**SECRET SIZE KEY BITS**	|	**PUBLIC SIZE KEY BITS**	|	**SIGN CLOCK CYCLES**	|	**SIGN TIME SECONDS**	|	**VERIFY CLOCK CYCLES**	|	**VERIFY TIME SECONDS**	|
|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|
|	PICNIC	|	 opt-l1full	|	sk-52-bytes	|	pk-35-bytes	|	3509982	|	 0.001852	|	2705433	|	 0.001428	|
|	GeMMS	|	 opt-128-Magenta	|	sk-16-bytes	|	pk-381-bytes	|	4008882	|	 0.002116	|	294503	|	 0.000155	|
|	GeMMS	|	 opt-128-Red	|	sk-16-bytes	|	pk-375-bytes	|	5030538	|	 0.002655	|	359647	|	 0.000190	|
|	PICNIC	|	 opt-l1fs	|	sk-49-bytes	|	pk-33-bytes	|	5401232	|	 0.002850	|	4320262	|	 0.002280	|
|	PICNIC	|	 opt-l1ur	|	sk-49-bytes	|	pk-33-bytes	|	6566576	|	 0.003465	|	5343424	|	 0.002820	|
|	PICNIC	|	 opt-l3full	|	sk-73-bytes	|	pk-49-bytes	|	7039587	|	 0.003715	|	5649518	|	 0.002981	|
|	GeMMS	|	 opt-192-Magenta	|	sk-24-bytes	|	pk-1348-bytes	|	8907855	|	 0.004701	|	605346	|	 0.000319	|
|	SPHINCS+	|	 opt-haraka-128f-simple	|	sk-64-bytes	|	pk-32-bytes	|	11136827	|	 0.005877	|	778203	|	 0.000411	|
|	PICNIC	|	 opt-l5full	|	sk-97-bytes	|	pk-65-bytes	|	11494532	|	 0.006066	|	9097239	|	 0.004801	|
|	GeMMS	|	 opt-192-Red	|	sk-24-bytes 	|	pk-1290-bytes	|	11881583	|	 0.006270	|	664214	|	 0.000351	|
|	PICNIC	|	 opt-l3fs	|	sk-73-bytes	|	pk-49-bytes	|	12166814	|	 0.006420	|	10010184	|	 0.005282	|
|	SPHINCS+	|	 opt-haraka-128f-robust	|	sk-64-bytes	|	pk-32-bytes	|	13331195	|	 0.007035	|	942040	|	 0.000497	|
|	PICNIC	|	 opt-l3ur	|	sk-73-bytes	|	pk-49-bytes	|	15364374	|	 0.008108	|	12617201	|	 0.006658	|
|	GeMMS	|	 opt-256-Red	|	sk-32-bytes	|	pk-3135-bytes	|	17261058	|	 0.009109	|	1502544	|	 0.000793	|
|	PICNIC	|	 opt-3l1	|	sk-52-bytes	|	pk-35-bytes	|	17636436	|	 0.009307	|	12901969	|	 0.006808	|
|	SPHINCS+	|	 opt-haraka-192f-simple	|	sk-96-bytes	|	pk-48-bytes	|	18731733	|	 0.009885	|	1124257	|	 0.000593	|
|	PICNIC	|	 opt-l5fs	|	sk-97-bytes	|	pk-65-bytes	|	21432757	|	 0.011310	|	17783390	|	 0.009384	|
|	GeMMS	|	 opt-256-Magenta	|	sk-32-bytes	|	pk-3321-bytes	|	21988363	|	 0.011603	|	1389599	|	 0.000733	|
|	SPHINCS+	|	 opt-haraka-192f-robust	|	sk-96-bytes	|	pk-48-bytes	|	26031285	|	 0.013737	|	1576761	|	 0.000832	|
|	PICNIC	|	 opt-l5ur	|	sk-97-bytes	|	pk-65-bytes	|	26465597	|	 0.013966	|	22131877	|	 0.011679	|
|	SPHINCS+	|	 opt-sha256-128f-simple	|	sk-64-bytes	|	pk-32-bytes	|	29932520	|	 0.015796	|	1987102	|	 0.001049	|
|	GeMMS	|	 ref-128-Magenta	|	sk-16-bytes	|	pk-381-bytes	|	31055628	|	 0.016388	|	325655	|	 0.000172	|
|	PICNIC	|	 opt-3l3	|	sk-73-bytes	|	pk-49-bytes	|	35983599	|	 0.018989	|	27098095	|	 0.014300	|
|	SPHINCS+	|	 opt-haraka-256f-simple	|	sk-128-bytes	|	pk-64-bytes	|	36528667	|	 0.019276	|	1133313	|	 0.000598	|
|	GeMMS	|	 ref-128-Red	|	sk-16-bytes	|	pk-375-bytes	|	43745543	|	 0.023085	|	377953	|	 0.000199	|
|	SPHINCS+	|	 opt-sha256-192f-simple	|	sk-96-bytes	|	pk-48-bytes	|	47928054	|	 0.025292	|	2996609	|	 0.001581	|
|	SPHINCS+	|	 opt-shake256-128f-simple	|	sk-64-bytes	|	pk-32-bytes	|	52202008	|	 0.027547	|	3138041	|	 0.001656	|
|	SPHINCS+	|	 opt-haraka-256f-robust	|	sk-128-bytes	|	pk-64-bytes	|	52434489	|	 0.027670	|	1614052	|	 0.000852	|
|	SPHINCS+	|	 opt-sha256-128f-robust	|	sk-64-bytes	|	pk-32-bytes	|	58342243	|	 0.030787	|	4058687	|	 0.002142	|
|	PICNIC	|	 ref-l1full	|	sk-52-bytes	|	pk-35-bytes	|	64237409	|	 0.033898	|	41659113	|	 0.021984	|
|	PICNIC	|	 opt-3l5	|	sk-97-bytes	|	pk-65-bytes	|	64350626	|	 0.033958	|	44259017	|	 0.023356	|
|	GeMMS	|	 ref-192-Magenta	|	sk-24-bytes	|	pk-1348-bytes	|	76041195	|	 0.040127	|	630495	|	 0.000333	|
|	SPHINCS+	|	 opt-shake256-192f-simple	|	sk-96-bytes	|	pk-48-bytes	|	82261430	|	 0.043410	|	4464260	|	 0.002356	|
|	SPHINCS+	|	 opt-sha256-256f-simple	|	sk-128-bytes	|	pk-64-bytes	|	94826551	|	 0.050040	|	3090222	|	 0.001631	|
|	SPHINCS+	|	 opt-sha256-192f-robust	|	sk-96-bytes	|	pk-48-bytes	|	96108168	|	 0.050717	|	6420516	|	 0.003388	|
|	SPHINCS+	|	 opt-shake256-128f-robust	|	sk-64-bytes	|	pk-32-bytes	|	99342882	|	 0.052424	|	6095363	|	 0.003217	|
|	GeMMS	|	 ref-192-Red	|	sk-24-bytes	|	pk-1290-bytes	|	109444746	|	 0.057754	|	692162	|	 0.000365	|
|	PICNIC	|	 ref-l1fs	|	sk-49-bytes	|	pk-33-bytes	|	110208445	|	 0.058157	|	71519807	|	 0.037741	|
|	GeMMS	|	 opt-128-Cyan	|	sk-16-bytes	|	pk-369-bytes	|	110219988	|	 0.058164	|	295174	|	 0.000156	|
|	SPHINCS+	|	 ref-sha256-128f-simple	|	sk-64-bytes	|	pk-32-bytes	|	113687284	|	 0.059993	|	6476639	|	 0.003418	|
|	PICNIC	|	 ref-l3full	|	sk-73-bytes	|	pk-49-bytes	|	129690728	|	 0.068438	|	84252399	|	 0.044460	|
|	PICNIC	|	 ref-l1ur	|	sk-49-bytes	|	pk-33-bytes	|	137992069	|	 0.072819	|	89816012	|	 0.047396	|
|	GeMMS	|	 ref-256-Red	|	sk-32-bytes	|	pk-3135-bytes	|	146538235	|	 0.077329	|	2030200	|	 0.001071	|
|	SPHINCS+	|	 opt-shake256-192f-robust	|	sk-96-bytes	|	pk-48-bytes	|	159150631	|	 0.083985	|	9086207	|	 0.004795	|
|	SPHINCS+	|	 opt-shake256-256f-simple	|	sk-128-bytes	|	pk-64-bytes	|	162835999	|	 0.085929	|	4609123	|	 0.002432	|
|	SPHINCS+	|	 ref-sha256-192f-simple	|	sk-96-bytes 	|	pk-48-bytes	|	191384208	|	 0.100994	|	9759597	|	 0.005150	|
|	SPHINCS+	|	 ref-haraka-128f-simple	|	sk-64-bytes 	|	pk-32-bytes	|	198685498	|	 0.104847	|	11979343	|	 0.006322	|
|	SPHINCS+	|	 ref-shake256-128f-simple	|	sk-64-bytes	|	pk-32-bytes	|	202690933	|	 0.106961	|	11339542	|	 0.005984	|
|	GeMMS	|	 ref-256-Magenta	|	sk-32-bytes	|	pk-3321-bytes	|	207087609	|	 0.109281	|	1387117	|	 0.000732	|
|	GeMMS	|	 opt-128-Blue	|	sk-16-bytes	|	pk-363-bytes	|	208390590	|	 0.109969	|	393253	|	 0.000208	|
|	SPHINCS+	|	 opt-haraka-128s-simple	|	sk-64-bytes	|	pk-32-bytes	|	220424158	|	 0.116319	|	296226	|	 0.000156	|
|	SPHINCS+	|	 ref-sha256-128f-robust	|	sk-64-bytes	|	pk-32-bytes	|	225254673	|	 0.118868	|	13447017	|	 0.007096	|
|	GeMMS	|	 ref-128-Cyan	|	sk-16-bytes	|	pk-369-bytes	|	263749715	|	 0.139182	|	323991	|	 0.000171	|
|	SPHINCS+	|	 opt-haraka-128s-robust	|	sk-64-bytes	|	pk-32-bytes	|	267784361	|	 0.141311	|	390411	|	 0.000206	|
|	SPHINCS+	|	 opt-shake256-256f-robust	|	sk-128-bytes	|	pk-64-bytes	|	305396860	|	 0.161159	|	8999803	|	 0.004749	|
|	GeMMS	|	 opt-192-Cyan	|	sk-24-bytes	|	pk-1320-bytes	|	315814609	|	 0.166657	|	649680	|	 0.000343	|
|	SPHINCS+	|	 ref-shake256-192f-simple	|	sk-96-bytes	|	pk-48-bytes	|	327599323	|	 0.172876	|	16823664	|	 0.008878	|
|	PICNIC	|	 ref-3l1	|	sk-52-bytes	|	pk-35-bytes	|	331163559	|	 0.174756	|	239883728	|	 0.126588	|
|	SPHINCS+	|	 ref-haraka-192f-simple	|	sk-96-bytes	|	pk-48-bytes	|	338740880	|	 0.178755	|	17681116	|	 0.009330	|
|	PICNIC	|	 ref-l3fs	|	sk-73-bytes	|	pk-49-bytes	|	350067042	|	 0.184732	|	229663543	|	 0.121194	|
|	SPHINCS+	|	 ref-haraka-128f-robust	|	sk-64-bytes	|	pk-32-bytes	|	375946666	|	 0.198389	|	22975984	|	 0.012125	|
|	SPHINCS+	|	 opt-sha256-256f-robust	|	sk-128-bytes	|	pk-64-bytes	|	376008334	|	 0.198421	|	12920808	|	 0.006818	|
|	SPHINCS+	|	 ref-sha256-192f-robust	|	sk-96-bytes	|	pk-48-bytes	|	379517060	|	 0.200273	|	20699864	|	 0.010923	|
|	SPHINCS+	|	 ref-sha256-256f-simple	|	sk-128-bytes	|	pk-64-bytes	|	387053976	|	 0.204250	|	10018587	|	 0.005287	|
|	SPHINCS+	|	 ref-shake256-128f-robust	|	sk-64-bytes	|	pk-32-bytes	|	388579849	|	 0.205055	|	22761856	|	 0.012012	|
|	SPHINCS+	|	 opt-haraka-256s-simple	|	sk-128-bytes	|	pk-64-bytes	|	393289093	|	 0.207540	|	613988	|	 0.000324	|
|	PICNIC	|	 ref-l3ur	|	sk-73-bytes	|	pk-49-bytes	|	417927607	|	 0.220542	|	280322137	|	 0.147927	|
|	GeMMS	|	 ref-128-Blue	|	sk-16-bytes	|	pk-363-bytes	|	427790363	|	 0.225747	|	431678	|	 0.000228	|
|	SPHINCS+	|	 opt-haraka-192s-simple	|	sk-96-bytes	|	pk-48-bytes	|	428270940	|	 0.226000	|	427886	|	 0.000226	|
|	GeMMS	|	 opt-192-Blue	|	sk-24-bytes	|	pk-1264-bytes	|	438858090	|	 0.231587	|	770449	|	 0.000407	|
|	GeMMS	|	 opt-256-Cyan	|	sk-32-bytes	|	pk-3272-bytes	|	512133163	|	 0.270255	|	1506921	|	 0.000795	|
|	GeMMS	|	 opt-256-Blue	|	sk-32-bytes	|	pk-3087-bytes	|	547145984	|	 0.288731	|	1814560	|	 0.000958	|
|	SPHINCS+	|	 opt-sha256-128s-simple	|	sk-64-bytes	|	pk-32-bytes	|	561808099	|	 0.296469	|	745864	|	 0.000394	|
|	SPHINCS+	|	 opt-haraka-256s-robust	|	sk-128-bytes	|	pk-64-bytes	|	580001887	|	 0.306070	|	912091	|	 0.000481	|
|	SPHINCS+	|	 opt-haraka-192s-robust	|	sk-96-bytes	|	pk-48-bytes	|	603139251	|	 0.318279	|	636208	|	 0.000336	|
|	SPHINCS+	|	 ref-shake256-192f-robust	|	sk-96-bytes	|	pk-48-bytes	|	620255285	|	 0.327311	|	33183463	|	 0.017511	|
|	SPHINCS+	|	 ref-haraka-192f-robust	|	sk-96-bytes	|	pk-48-bytes	|	642478970	|	 0.339039	|	35178411	|	 0.018564	|
|	SPHINCS+	|	 ref-shake256-256f-simple	|	sk-128-bytes	|	pk-64-bytes	|	645670532	|	 0.340723	|	16840156	|	 0.008887	|
|	PICNIC	|	 ref-l5full	|	sk-97-bytes	|	pk-65-bytes	|	697071977	|	 0.367848	|	460149759	|	 0.242823	|
|	SPHINCS+	|	 ref-haraka-256f-simple	|	sk-128-bytes	|	pk-64-bytes	|	712865920	|	 0.376183	|	18868611	|	 0.009957	|
|	PICNIC	|	 ref-3l3	|	sk-73-bytes	|	pk-49-bytes	|	774850743	|	 0.408892	|	547471809	|	 0.288903	|
|	PICNIC	|	 ref-l5fs	|	sk-97-bytes	|	pk-65-bytes	|	828262061	|	 0.437078	|	535470417	|	 0.282570	|
|	GeMMS	|	 ref-192-Cyan	|	sk-24-bytes	|	pk-1320-bytes	|	866155103	|	 0.457074	|	627598	|	 0.000331	|
|	SPHINCS+	|	 opt-sha256-256s-simple	|	sk-128-bytes	|	pk-64-bytes	|	891060243	|	 0.470216	|	1755870	|	 0.000927	|
|	PICNIC	|	 ref-l5ur	|	sk-97-bytes	|	pk-65-bytes	|	929758348	|	 0.490638	|	609858792	|	 0.321825	|
|	GeMMS	|	 opt-128-White	|	sk-16-bytes	|	pk-358-bytes	|	988456680	|	 0.521613	|	313054	|	 0.000165	|
|	SPHINCS+	|	 opt-shake256-128s-simple	|	sk-64-bytes	|	pk-32-bytes	|	1027474185	|	 0.542203	|	1104626	|	 0.000583	|
|	SPHINCS+	|	 opt-sha256-192s-simple	|	sk-96-bytes	|	pk-48-bytes	|	1073623882	|	 0.566556	|	1251542	|	 0.000660	|
|	SPHINCS+	|	 ref-sha256-256f-robust	|	sk-128-bytes	|	pk-64-bytes	|	1100571026	|	 0.580776	|	31458578	|	 0.016601	|
|	SPHINCS+	|	 opt-sha256-128s-robust	|	sk-64-bytes	|	pk-32-bytes	|	1143870081	|	 0.603625	|	1548909	|	 0.000817	|
|	GeMMS	|	 opt-128	|	sk-16-bytes	|	pk-352-bytes	|	1212913275	|	 0.640060	|	350059	|	 0.000185	|
|	SPHINCS+	|	 ref-shake256-256f-robust	|	sk-128-bytes	|	pk-64-bytes	|	1230747715	|	 0.649471	|	33829605	|	 0.017852	|
|	GeMMS	|	 ref-192-Blue	|	sk-24-bytes	|	pk-1264-bytes	|	1238209633	|	 0.653409	|	996840	|	 0.000526	|
|	SPHINCS+	|	 ref-haraka-256f-robust	|	sk-128-bytes	|	pk-64-bytes	|	1326496960	|	 0.699998	|	37006107	|	 0.019528	|
|	GeMMS	|	 ref-256-Blue	|	sk-32-bytes	|	pk-3087-bytes	|	1405246424	|	 0.741555	|	2492633	|	 0.001315	|
|	GeMMS	|	 ref-256-Cyan	|	sk-32-bytes	|	pk-3272-bytes	|	1434646087	|	 0.757069	|	1921906	|	 0.001014	|
|	SPHINCS+	|	 opt-shake256-256s-simple	|	sk-128-bytes	|	pk-64-bytes	|	1533961135	|	 0.809478	|	2289214	|	 0.001208	|
|	PICNIC	|	 ref-3l5	|	sk-97-bytes	|	pk-65-bytes	|	1755021313	|	 0.926133	|	1097661402	|	 0.579241	|
|	SPHINCS+	|	 opt-shake256-192s-simple	|	sk-96-bytes	|	pk-48-bytes	|	1788877298	|	 0.943999	|	1589768	|	 0.000839	|
|	GeMMS	|	 ref-128-White	|	sk-16-bytes	|	pk-358-bytes	|	1804540056	|	 0.952264	|	319629	|	 0.000169	|
|	SPHINCS+	|	 opt-shake256-128s-robust	|	sk-64-bytes	|	pk-32-bytes	|	1959098329	|	 1.033825	|	2295827	|	 0.001212	|
|	SPHINCS+	|	 opt-sha256-192s-robust	|	sk-96-bytes	|	pk-48-bytes	|	2158505721	|	 1.139053	|	2646088	|	 0.001396	|
|	GeMMS	|	 ref-128	|	sk-16-bytes	|	pk-352-bytes	|	2188086605	|	 1.154663	|	391618	|	 0.000207	|
|	SPHINCS+	|	 ref-sha256-128s-simple	|	sk-64-bytes	|	pk-32-bytes	|	2235907404	|	 1.179898	|	2252711	|	 0.001189	|
|	GeMMS	|	 opt-192-White	|	sk-24-bytes	|	pk-1293-bytes	|	2285773322	|	 1.206213	|	653292	|	 0.000345	|
|	GeMMS	|	 opt-192	|	sk-24-bytes	|	pk-1237-bytes	|	2774938715	|	 1.464348	|	819409	|	 0.000432	|
|	SPHINCS+	|	 opt-shake256-256s-robust	|	sk-128-bytes	|	pk-64-bytes	|	2973313803	|	 1.569031	|	4965339	|	 0.002620	|
|	SPHINCS+	|	 opt-sha256-256s-robust	|	sk-128-bytes	|	pk-64-bytes	|	3411463804	|	 1.800245	|	6953306	|	 0.003669	|
|	SPHINCS+	|	 opt-shake256-192s-robust	|	sk-96-bytes	|	pk-48-bytes	|	3477264086	|	 1.834968	|	3199557	|	 0.001688	|
|	SPHINCS+	|	 ref-sha256-256s-simple	|	sk-128-bytes	|	pk-64-bytes	|	3747593333	|	 1.977622	|	5160641	|	 0.002723	|
|	GeMMS	|	 opt-256-White	|	sk-32-bytes	|	pk-3222-bytes	|	3918630253	|	 2.067879	|	1513814	|	 0.000799	|
|	SPHINCS+	|	 ref-haraka-128s-simple	|	sk-64-bytes	|	pk-32-bytes	|	3958683984	|	 2.089015	|	4508226	|	 0.002379	|
|	SPHINCS+	|	 ref-shake256-128s-simple	|	sk-64-bytes	|	pk-32-bytes	|	3986844625	|	 2.103876	|	3864892	|	 0.002040	|
|	SPHINCS+	|	 ref-sha256-192s-simple	|	sk-96-bytes	|	pk-48-bytes	|	4136636083	|	 2.182921	|	3563568	|	 0.001881	|
|	SPHINCS+	|	 ref-sha256-128s-robust	|	sk-64-bytes	|	pk-32-bytes	|	4440339160	|	 2.343187	|	4549639	|	 0.002401	|
|	GeMMS	|	 opt-256	|	sk-32-bytes	|	pk-3040-bytes	|	4553723238	|	 2.403020	|	2937114	|	 0.001550	|
|	GeMMS	|	 ref-192-White	|	sk-24-bytes	|	pk-1293-bytes	|	4877693967	|	 2.573981	|	709189	|	 0.000374	|
|	GeMMS	|	 ref-192	|	sk-24-bytes	|	pk-1237-bytes	|	5791811784	|	 3.056365	|	866833	|	 0.000457	|
|	SPHINCS+	|	 ref-shake256-256s-simple	|	sk-128-bytes	|	pk-64-bytes	|	5985636847	|	 3.158647	|	8289717	|	 0.004375	|
|	SPHINCS+	|	 ref-shake256-192s-simple	|	sk-96-bytes	|	pk-48-bytes	|	6840284925	|	 3.609649	|	5599161	|	 0.002955	|
|	SPHINCS+	|	 ref-haraka-128s-robust	|	sk-64-bytes	|	pk-32-bytes	|	7457464764	|	 3.935338	|	8634684	|	 0.004557	|
|	SPHINCS+	|	 ref-haraka-192s-simple	|	sk-96-bytes	|	pk-48-bytes	|	7482127014	|	 3.948352	|	6591137	|	 0.003478	|
|	GeMMS	|	 ref-256-White	|	sk-32-bytes	|	pk-3222-bytes	|	7492453936	|	 3.953802	|	1524849	|	 0.000805	|
|	SPHINCS+	|	 ref-haraka-256s-simple	|	sk-128-bytes	|	pk-64-bytes	|	7510276191	|	 3.963206	|	10216859	|	 0.005391	|
|	SPHINCS+	|	 ref-shake256-128s-robust	|	sk-64-bytes	|	pk-32-bytes	|	7642030101	|	 4.032734	|	7865875	|	 0.004151	|
|	GeMMS	|	 ref-256	|	sk-32-bytes	|	pk-3040-bytes	|	7876869188	|	 4.156659	|	2227358	|	 0.001175	|
|	SPHINCS+	|	 ref-sha256-192s-robust	|	sk-96-bytes	|	pk-48-bytes	|	8160136266	|	 4.306141	|	7297520	|	 0.003851	|
|	SPHINCS+	|	 ref-sha256-256s-robust	|	sk-128-bytes	|	pk-64-bytes	|	10383702264	|	 5.479526	|	15966666	|	 0.008426	|
|	SPHINCS+	|	 ref-shake256-256s-robust	|	sk-128-bytes	|	pk-64-bytes	|	11220405903	|	 5.921059	|	16760828	|	 0.008845	|
|	SPHINCS+	|	 ref-shake256-192s-robust	|	sk-96-bytes	|	pk-48-bytes	|	12968415707	|	 6.843491	|	11333563	|	 0.005981	|
|	SPHINCS+	|	 ref-haraka-256s-robust	|	sk-128-bytes	|	pk-64-bytes	|	13568744782	|	 7.160287	|	19994534	|	 0.010551	|
|	SPHINCS+	|	 ref-haraka-192s-robust	|	sk-96-bytes	|	pk-48-bytes	|	14097140913	|	 7.439124	|	13345974	|	 0.007043	|


**Alternative Candidates Verification**
|	**SIGNATURE NAME**	|	**VERSION**	|	**SECRET SIZE KEY BITS**	|	**PUBLIC SIZE KEY BITS**	|	**SIGN CLOCK CYCLES**	|	**SIGN TIME SECONDS**	|	**VERIFY CLOCK CYCLES**	|	**VERIFY TIME SECONDS**	|
|	---	|	---	|	---	|	---	|	---	|	---	|	---	|	---	|
|	GeMMS	|	 opt-128-Magenta	|	sk-16-bytes	|	pk-381-bytes	|	4008882	|	 0.002116	|	294503	|	 0.000155	|
|	GeMMS	|	 opt-128-Cyan	|	sk-16-bytes	|	pk-369-bytes	|	110219988	|	 0.058164	|	295174	|	 0.000156	|
|	SPHINCS+	|	 opt-haraka-128s-simple	|	sk-64-bytes	|	pk-32-bytes	|	220424158	|	 0.116319	|	296226	|	 0.000156	|
|	GeMMS	|	 opt-128-White	|	sk-16-bytes	|	pk-358-bytes	|	988456680	|	 0.521613	|	313054	|	 0.000165	|
|	GeMMS	|	 ref-128-White	|	sk-16-bytes	|	pk-358-bytes	|	1804540056	|	 0.952264	|	319629	|	 0.000169	|
|	GeMMS	|	 ref-128-Cyan	|	sk-16-bytes	|	pk-369-bytes	|	263749715	|	 0.139182	|	323991	|	 0.000171	|
|	GeMMS	|	 ref-128-Magenta	|	sk-16-bytes	|	pk-381-bytes	|	31055628	|	 0.016388	|	325655	|	 0.000172	|
|	GeMMS	|	 opt-128	|	sk-16-bytes	|	pk-352-bytes	|	1212913275	|	 0.640060	|	350059	|	 0.000185	|
|	GeMMS	|	 opt-128-Red	|	sk-16-bytes	|	pk-375-bytes	|	5030538	|	 0.002655	|	359647	|	 0.000190	|
|	GeMMS	|	 ref-128-Red	|	sk-16-bytes	|	pk-375-bytes	|	43745543	|	 0.023085	|	377953	|	 0.000199	|
|	SPHINCS+	|	 opt-haraka-128s-robust	|	sk-64-bytes	|	pk-32-bytes	|	267784361	|	 0.141311	|	390411	|	 0.000206	|
|	GeMMS	|	 ref-128	|	sk-16-bytes	|	pk-352-bytes	|	2188086605	|	 1.154663	|	391618	|	 0.000207	|
|	GeMMS	|	 opt-128-Blue	|	sk-16-bytes	|	pk-363-bytes	|	208390590	|	 0.109969	|	393253	|	 0.000208	|
|	SPHINCS+	|	 opt-haraka-192s-simple	|	sk-96-bytes	|	pk-48-bytes	|	428270940	|	 0.226000	|	427886	|	 0.000226	|
|	GeMMS	|	 ref-128-Blue	|	sk-16-bytes	|	pk-363-bytes	|	427790363	|	 0.225747	|	431678	|	 0.000228	|
|	GeMMS	|	 opt-192-Magenta	|	sk-24-bytes	|	pk-1348-bytes	|	8907855	|	 0.004701	|	605346	|	 0.000319	|
|	SPHINCS+	|	 opt-haraka-256s-simple	|	sk-128-bytes	|	pk-64-bytes	|	393289093	|	 0.207540	|	613988	|	 0.000324	|
|	GeMMS	|	 ref-192-Cyan	|	sk-24-bytes	|	pk-1320-bytes	|	866155103	|	 0.457074	|	627598	|	 0.000331	|
|	GeMMS	|	 ref-192-Magenta	|	sk-24-bytes	|	pk-1348-bytes	|	76041195	|	 0.040127	|	630495	|	 0.000333	|
|	SPHINCS+	|	 opt-haraka-192s-robust	|	sk-96-bytes	|	pk-48-bytes	|	603139251	|	 0.318279	|	636208	|	 0.000336	|
|	GeMMS	|	 opt-192-Cyan	|	sk-24-bytes	|	pk-1320-bytes	|	315814609	|	 0.166657	|	649680	|	 0.000343	|
|	GeMMS	|	 opt-192-White	|	sk-24-bytes	|	pk-1293-bytes	|	2285773322	|	 1.206213	|	653292	|	 0.000345	|
|	GeMMS	|	 opt-192-Red	|	sk-24-bytes 	|	pk-1290-bytes	|	11881583	|	 0.006270	|	664214	|	 0.000351	|
|	GeMMS	|	 ref-192-Red	|	sk-24-bytes	|	pk-1290-bytes	|	109444746	|	 0.057754	|	692162	|	 0.000365	|
|	GeMMS	|	 ref-192-White	|	sk-24-bytes	|	pk-1293-bytes	|	4877693967	|	 2.573981	|	709189	|	 0.000374	|
|	SPHINCS+	|	 opt-sha256-128s-simple	|	sk-64-bytes	|	pk-32-bytes	|	561808099	|	 0.296469	|	745864	|	 0.000394	|
|	GeMMS	|	 opt-192-Blue	|	sk-24-bytes	|	pk-1264-bytes	|	438858090	|	 0.231587	|	770449	|	 0.000407	|
|	SPHINCS+	|	 opt-haraka-128f-simple	|	sk-64-bytes	|	pk-32-bytes	|	11136827	|	 0.005877	|	778203	|	 0.000411	|
|	GeMMS	|	 opt-192	|	sk-24-bytes	|	pk-1237-bytes	|	2774938715	|	 1.464348	|	819409	|	 0.000432	|
|	GeMMS	|	 ref-192	|	sk-24-bytes	|	pk-1237-bytes	|	5791811784	|	 3.056365	|	866833	|	 0.000457	|
|	SPHINCS+	|	 opt-haraka-256s-robust	|	sk-128-bytes	|	pk-64-bytes	|	580001887	|	 0.306070	|	912091	|	 0.000481	|
|	SPHINCS+	|	 opt-haraka-128f-robust	|	sk-64-bytes	|	pk-32-bytes	|	13331195	|	 0.007035	|	942040	|	 0.000497	|
|	GeMMS	|	 ref-192-Blue	|	sk-24-bytes	|	pk-1264-bytes	|	1238209633	|	 0.653409	|	996840	|	 0.000526	|
|	SPHINCS+	|	 opt-shake256-128s-simple	|	sk-64-bytes	|	pk-32-bytes	|	1027474185	|	 0.542203	|	1104626	|	 0.000583	|
|	SPHINCS+	|	 opt-haraka-192f-simple	|	sk-96-bytes	|	pk-48-bytes	|	18731733	|	 0.009885	|	1124257	|	 0.000593	|
|	SPHINCS+	|	 opt-haraka-256f-simple	|	sk-128-bytes	|	pk-64-bytes	|	36528667	|	 0.019276	|	1133313	|	 0.000598	|
|	SPHINCS+	|	 opt-sha256-192s-simple	|	sk-96-bytes	|	pk-48-bytes	|	1073623882	|	 0.566556	|	1251542	|	 0.000660	|
|	GeMMS	|	 ref-256-Magenta	|	sk-32-bytes	|	pk-3321-bytes	|	207087609	|	 0.109281	|	1387117	|	 0.000732	|
|	GeMMS	|	 opt-256-Magenta	|	sk-32-bytes	|	pk-3321-bytes	|	21988363	|	 0.011603	|	1389599	|	 0.000733	|
|	GeMMS	|	 opt-256-Red	|	sk-32-bytes	|	pk-3135-bytes	|	17261058	|	 0.009109	|	1502544	|	 0.000793	|
|	GeMMS	|	 opt-256-Cyan	|	sk-32-bytes	|	pk-3272-bytes	|	512133163	|	 0.270255	|	1506921	|	 0.000795	|
|	GeMMS	|	 opt-256-White	|	sk-32-bytes	|	pk-3222-bytes	|	3918630253	|	 2.067879	|	1513814	|	 0.000799	|
|	GeMMS	|	 ref-256-White	|	sk-32-bytes	|	pk-3222-bytes	|	7492453936	|	 3.953802	|	1524849	|	 0.000805	|
|	SPHINCS+	|	 opt-sha256-128s-robust	|	sk-64-bytes	|	pk-32-bytes	|	1143870081	|	 0.603625	|	1548909	|	 0.000817	|
|	SPHINCS+	|	 opt-haraka-192f-robust	|	sk-96-bytes	|	pk-48-bytes	|	26031285	|	 0.013737	|	1576761	|	 0.000832	|
|	SPHINCS+	|	 opt-shake256-192s-simple	|	sk-96-bytes	|	pk-48-bytes	|	1788877298	|	 0.943999	|	1589768	|	 0.000839	|
|	SPHINCS+	|	 opt-haraka-256f-robust	|	sk-128-bytes	|	pk-64-bytes	|	52434489	|	 0.027670	|	1614052	|	 0.000852	|
|	SPHINCS+	|	 opt-sha256-256s-simple	|	sk-128-bytes	|	pk-64-bytes	|	891060243	|	 0.470216	|	1755870	|	 0.000927	|
|	GeMMS	|	 opt-256-Blue	|	sk-32-bytes	|	pk-3087-bytes	|	547145984	|	 0.288731	|	1814560	|	 0.000958	|
|	GeMMS	|	 ref-256-Cyan	|	sk-32-bytes	|	pk-3272-bytes	|	1434646087	|	 0.757069	|	1921906	|	 0.001014	|
|	SPHINCS+	|	 opt-sha256-128f-simple	|	sk-64-bytes	|	pk-32-bytes	|	29932520	|	 0.015796	|	1987102	|	 0.001049	|
|	GeMMS	|	 ref-256-Red	|	sk-32-bytes	|	pk-3135-bytes	|	146538235	|	 0.077329	|	2030200	|	 0.001071	|
|	GeMMS	|	 ref-256	|	sk-32-bytes	|	pk-3040-bytes	|	7876869188	|	 4.156659	|	2227358	|	 0.001175	|
|	SPHINCS+	|	 ref-sha256-128s-simple	|	sk-64-bytes	|	pk-32-bytes	|	2235907404	|	 1.179898	|	2252711	|	 0.001189	|
|	SPHINCS+	|	 opt-shake256-256s-simple	|	sk-128-bytes	|	pk-64-bytes	|	1533961135	|	 0.809478	|	2289214	|	 0.001208	|
|	SPHINCS+	|	 opt-shake256-128s-robust	|	sk-64-bytes	|	pk-32-bytes	|	1959098329	|	 1.033825	|	2295827	|	 0.001212	|
|	GeMMS	|	 ref-256-Blue	|	sk-32-bytes	|	pk-3087-bytes	|	1405246424	|	 0.741555	|	2492633	|	 0.001315	|
|	SPHINCS+	|	 opt-sha256-192s-robust	|	sk-96-bytes	|	pk-48-bytes	|	2158505721	|	 1.139053	|	2646088	|	 0.001396	|
|	PICNIC	|	 opt-l1full	|	sk-52-bytes	|	pk-35-bytes	|	3509982	|	 0.001852	|	2705433	|	 0.001428	|
|	GeMMS	|	 opt-256	|	sk-32-bytes	|	pk-3040-bytes	|	4553723238	|	 2.403020	|	2937114	|	 0.001550	|
|	SPHINCS+	|	 opt-sha256-192f-simple	|	sk-96-bytes	|	pk-48-bytes	|	47928054	|	 0.025292	|	2996609	|	 0.001581	|
|	SPHINCS+	|	 opt-sha256-256f-simple	|	sk-128-bytes	|	pk-64-bytes	|	94826551	|	 0.050040	|	3090222	|	 0.001631	|
|	SPHINCS+	|	 opt-shake256-128f-simple	|	sk-64-bytes	|	pk-32-bytes	|	52202008	|	 0.027547	|	3138041	|	 0.001656	|
|	SPHINCS+	|	 opt-shake256-192s-robust	|	sk-96-bytes	|	pk-48-bytes	|	3477264086	|	 1.834968	|	3199557	|	 0.001688	|
|	SPHINCS+	|	 ref-sha256-192s-simple	|	sk-96-bytes	|	pk-48-bytes	|	4136636083	|	 2.182921	|	3563568	|	 0.001881	|
|	SPHINCS+	|	 ref-shake256-128s-simple	|	sk-64-bytes	|	pk-32-bytes	|	3986844625	|	 2.103876	|	3864892	|	 0.002040	|
|	SPHINCS+	|	 opt-sha256-128f-robust	|	sk-64-bytes	|	pk-32-bytes	|	58342243	|	 0.030787	|	4058687	|	 0.002142	|
|	PICNIC	|	 opt-l1fs	|	sk-49-bytes	|	pk-33-bytes	|	5401232	|	 0.002850	|	4320262	|	 0.002280	|
|	SPHINCS+	|	 opt-shake256-192f-simple	|	sk-96-bytes	|	pk-48-bytes	|	82261430	|	 0.043410	|	4464260	|	 0.002356	|
|	SPHINCS+	|	 ref-haraka-128s-simple	|	sk-64-bytes	|	pk-32-bytes	|	3958683984	|	 2.089015	|	4508226	|	 0.002379	|
|	SPHINCS+	|	 ref-sha256-128s-robust	|	sk-64-bytes	|	pk-32-bytes	|	4440339160	|	 2.343187	|	4549639	|	 0.002401	|
|	SPHINCS+	|	 opt-shake256-256f-simple	|	sk-128-bytes	|	pk-64-bytes	|	162835999	|	 0.085929	|	4609123	|	 0.002432	|
|	SPHINCS+	|	 opt-shake256-256s-robust	|	sk-128-bytes	|	pk-64-bytes	|	2973313803	|	 1.569031	|	4965339	|	 0.002620	|
|	SPHINCS+	|	 ref-sha256-256s-simple	|	sk-128-bytes	|	pk-64-bytes	|	3747593333	|	 1.977622	|	5160641	|	 0.002723	|
|	PICNIC	|	 opt-l1ur	|	sk-49-bytes	|	pk-33-bytes	|	6566576	|	 0.003465	|	5343424	|	 0.002820	|
|	SPHINCS+	|	 ref-shake256-192s-simple	|	sk-96-bytes	|	pk-48-bytes	|	6840284925	|	 3.609649	|	5599161	|	 0.002955	|
|	PICNIC	|	 opt-l3full	|	sk-73-bytes	|	pk-49-bytes	|	7039587	|	 0.003715	|	5649518	|	 0.002981	|
|	SPHINCS+	|	 opt-shake256-128f-robust	|	sk-64-bytes	|	pk-32-bytes	|	99342882	|	 0.052424	|	6095363	|	 0.003217	|
|	SPHINCS+	|	 opt-sha256-192f-robust	|	sk-96-bytes	|	pk-48-bytes	|	96108168	|	 0.050717	|	6420516	|	 0.003388	|
|	SPHINCS+	|	 ref-sha256-128f-simple	|	sk-64-bytes	|	pk-32-bytes	|	113687284	|	 0.059993	|	6476639	|	 0.003418	|
|	SPHINCS+	|	 ref-haraka-192s-simple	|	sk-96-bytes	|	pk-48-bytes	|	7482127014	|	 3.948352	|	6591137	|	 0.003478	|
|	SPHINCS+	|	 opt-sha256-256s-robust	|	sk-128-bytes	|	pk-64-bytes	|	3411463804	|	 1.800245	|	6953306	|	 0.003669	|
|	SPHINCS+	|	 ref-sha256-192s-robust	|	sk-96-bytes	|	pk-48-bytes	|	8160136266	|	 4.306141	|	7297520	|	 0.003851	|
|	SPHINCS+	|	 ref-shake256-128s-robust	|	sk-64-bytes	|	pk-32-bytes	|	7642030101	|	 4.032734	|	7865875	|	 0.004151	|
|	SPHINCS+	|	 ref-shake256-256s-simple	|	sk-128-bytes	|	pk-64-bytes	|	5985636847	|	 3.158647	|	8289717	|	 0.004375	|
|	SPHINCS+	|	 ref-haraka-128s-robust	|	sk-64-bytes	|	pk-32-bytes	|	7457464764	|	 3.935338	|	8634684	|	 0.004557	|
|	SPHINCS+	|	 opt-shake256-256f-robust	|	sk-128-bytes	|	pk-64-bytes	|	305396860	|	 0.161159	|	8999803	|	 0.004749	|
|	SPHINCS+	|	 opt-shake256-192f-robust	|	sk-96-bytes	|	pk-48-bytes	|	159150631	|	 0.083985	|	9086207	|	 0.004795	|
|	PICNIC	|	 opt-l5full	|	sk-97-bytes	|	pk-65-bytes	|	11494532	|	 0.006066	|	9097239	|	 0.004801	|
|	SPHINCS+	|	 ref-sha256-192f-simple	|	sk-96-bytes 	|	pk-48-bytes	|	191384208	|	 0.100994	|	9759597	|	 0.005150	|
|	PICNIC	|	 opt-l3fs	|	sk-73-bytes	|	pk-49-bytes	|	12166814	|	 0.006420	|	10010184	|	 0.005282	|
|	SPHINCS+	|	 ref-sha256-256f-simple	|	sk-128-bytes	|	pk-64-bytes	|	387053976	|	 0.204250	|	10018587	|	 0.005287	|
|	SPHINCS+	|	 ref-haraka-256s-simple	|	sk-128-bytes	|	pk-64-bytes	|	7510276191	|	 3.963206	|	10216859	|	 0.005391	|
|	SPHINCS+	|	 ref-shake256-192s-robust	|	sk-96-bytes	|	pk-48-bytes	|	12968415707	|	 6.843491	|	11333563	|	 0.005981	|
|	SPHINCS+	|	 ref-shake256-128f-simple	|	sk-64-bytes	|	pk-32-bytes	|	202690933	|	 0.106961	|	11339542	|	 0.005984	|
|	SPHINCS+	|	 ref-haraka-128f-simple	|	sk-64-bytes 	|	pk-32-bytes	|	198685498	|	 0.104847	|	11979343	|	 0.006322	|
|	PICNIC	|	 opt-l3ur	|	sk-73-bytes	|	pk-49-bytes	|	15364374	|	 0.008108	|	12617201	|	 0.006658	|
|	PICNIC	|	 opt-3l1	|	sk-52-bytes	|	pk-35-bytes	|	17636436	|	 0.009307	|	12901969	|	 0.006808	|
|	SPHINCS+	|	 opt-sha256-256f-robust	|	sk-128-bytes	|	pk-64-bytes	|	376008334	|	 0.198421	|	12920808	|	 0.006818	|
|	SPHINCS+	|	 ref-haraka-192s-robust	|	sk-96-bytes	|	pk-48-bytes	|	14097140913	|	 7.439124	|	13345974	|	 0.007043	|
|	SPHINCS+	|	 ref-sha256-128f-robust	|	sk-64-bytes	|	pk-32-bytes	|	225254673	|	 0.118868	|	13447017	|	 0.007096	|
|	SPHINCS+	|	 ref-sha256-256s-robust	|	sk-128-bytes	|	pk-64-bytes	|	10383702264	|	 5.479526	|	15966666	|	 0.008426	|
|	SPHINCS+	|	 ref-shake256-256s-robust	|	sk-128-bytes	|	pk-64-bytes	|	11220405903	|	 5.921059	|	16760828	|	 0.008845	|
|	SPHINCS+	|	 ref-shake256-192f-simple	|	sk-96-bytes	|	pk-48-bytes	|	327599323	|	 0.172876	|	16823664	|	 0.008878	|
|	SPHINCS+	|	 ref-shake256-256f-simple	|	sk-128-bytes	|	pk-64-bytes	|	645670532	|	 0.340723	|	16840156	|	 0.008887	|
|	SPHINCS+	|	 ref-haraka-192f-simple	|	sk-96-bytes	|	pk-48-bytes	|	338740880	|	 0.178755	|	17681116	|	 0.009330	|
|	PICNIC	|	 opt-l5fs	|	sk-97-bytes	|	pk-65-bytes	|	21432757	|	 0.011310	|	17783390	|	 0.009384	|
|	SPHINCS+	|	 ref-haraka-256f-simple	|	sk-128-bytes	|	pk-64-bytes	|	712865920	|	 0.376183	|	18868611	|	 0.009957	|
|	SPHINCS+	|	 ref-haraka-256s-robust	|	sk-128-bytes	|	pk-64-bytes	|	13568744782	|	 7.160287	|	19994534	|	 0.010551	|
|	SPHINCS+	|	 ref-sha256-192f-robust	|	sk-96-bytes	|	pk-48-bytes	|	379517060	|	 0.200273	|	20699864	|	 0.010923	|
|	PICNIC	|	 opt-l5ur	|	sk-97-bytes	|	pk-65-bytes	|	26465597	|	 0.013966	|	22131877	|	 0.011679	|
|	SPHINCS+	|	 ref-shake256-128f-robust	|	sk-64-bytes	|	pk-32-bytes	|	388579849	|	 0.205055	|	22761856	|	 0.012012	|
|	SPHINCS+	|	 ref-haraka-128f-robust	|	sk-64-bytes	|	pk-32-bytes	|	375946666	|	 0.198389	|	22975984	|	 0.012125	|
|	PICNIC	|	 opt-3l3	|	sk-73-bytes	|	pk-49-bytes	|	35983599	|	 0.018989	|	27098095	|	 0.014300	|
|	SPHINCS+	|	 ref-sha256-256f-robust	|	sk-128-bytes	|	pk-64-bytes	|	1100571026	|	 0.580776	|	31458578	|	 0.016601	|
|	SPHINCS+	|	 ref-shake256-192f-robust	|	sk-96-bytes	|	pk-48-bytes	|	620255285	|	 0.327311	|	33183463	|	 0.017511	|
|	SPHINCS+	|	 ref-shake256-256f-robust	|	sk-128-bytes	|	pk-64-bytes	|	1230747715	|	 0.649471	|	33829605	|	 0.017852	|
|	SPHINCS+	|	 ref-haraka-192f-robust	|	sk-96-bytes	|	pk-48-bytes	|	642478970	|	 0.339039	|	35178411	|	 0.018564	|
|	SPHINCS+	|	 ref-haraka-256f-robust	|	sk-128-bytes	|	pk-64-bytes	|	1326496960	|	 0.699998	|	37006107	|	 0.019528	|
|	PICNIC	|	 ref-l1full	|	sk-52-bytes	|	pk-35-bytes	|	64237409	|	 0.033898	|	41659113	|	 0.021984	|
|	PICNIC	|	 opt-3l5	|	sk-97-bytes	|	pk-65-bytes	|	64350626	|	 0.033958	|	44259017	|	 0.023356	|
|	PICNIC	|	 ref-l1fs	|	sk-49-bytes	|	pk-33-bytes	|	110208445	|	 0.058157	|	71519807	|	 0.037741	|
|	PICNIC	|	 ref-l3full	|	sk-73-bytes	|	pk-49-bytes	|	129690728	|	 0.068438	|	84252399	|	 0.044460	|
|	PICNIC	|	 ref-l1ur	|	sk-49-bytes	|	pk-33-bytes	|	137992069	|	 0.072819	|	89816012	|	 0.047396	|
|	PICNIC	|	 ref-l3fs	|	sk-73-bytes	|	pk-49-bytes	|	350067042	|	 0.184732	|	229663543	|	 0.121194	|
|	PICNIC	|	 ref-3l1	|	sk-52-bytes	|	pk-35-bytes	|	331163559	|	 0.174756	|	239883728	|	 0.126588	|
|	PICNIC	|	 ref-l3ur	|	sk-73-bytes	|	pk-49-bytes	|	417927607	|	 0.220542	|	280322137	|	 0.147927	|
|	PICNIC	|	 ref-l5full	|	sk-97-bytes	|	pk-65-bytes	|	697071977	|	 0.367848	|	460149759	|	 0.242823	|
|	PICNIC	|	 ref-l5fs	|	sk-97-bytes	|	pk-65-bytes	|	828262061	|	 0.437078	|	535470417	|	 0.282570	|
|	PICNIC	|	 ref-3l3	|	sk-73-bytes	|	pk-49-bytes	|	774850743	|	 0.408892	|	547471809	|	 0.288903	|
|	PICNIC	|	 ref-l5ur	|	sk-97-bytes	|	pk-65-bytes	|	929758348	|	 0.490638	|	609858792	|	 0.321825	|
|	PICNIC	|	 ref-3l5	|	sk-97-bytes	|	pk-65-bytes	|	1755021313	|	 0.926133	|	1097661402	|	 0.579241	|


