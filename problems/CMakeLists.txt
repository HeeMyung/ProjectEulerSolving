function(myexe target_name file_name)
	include_directories(${MY_INCLUDES})
	add_executable(${target_name} ${file_name})
	set_target_properties(${target_name} 
		PROPERTIES 
		FOLDER 
		"Problems"
	)
	target_link_libraries(${target_name} ${MY_LIBS})
endfunction(myexe)
myexe(Problem100 "100_discProbability.cpp")
myexe(Problem101 "101_badopsum.cpp")
myexe(Problem102 "102_triangleIncludeOrigin.cpp")
myexe(Problem103 "103_optSpecialSumSet.cpp")
myexe(Problem104 "104_fibonaccipandigital.cpp")
myexe(Problem105 "105_checkSpecialSumSet.cpp")
myexe(Problem106 "106_SpecialSumSetCheckCount.cpp")
myexe(Problem107 "107_RemoveEdghWithoutDisconnect.cpp")
myexe(Problem108 "108_diophantosequation.cpp")
myexe(Problem109 "109_dartFinish.cpp")
myexe(Problem110 "110_diophantosequationEx.cpp")
myexe(Problem111 "111_primeRepeatNumber.cpp")
myexe(Problem112 "112_bouncyNumber.cpp")
myexe(Problem113 "113_boucyNumberEx.cpp")
myexe(Problem114 "114_blockPlaceProblem.cpp")
myexe(Problem115 "115_blockPlaceProblemEx.cpp")
myexe(Problem116 "116_blockPlaceNoMixProblem.cpp")
myexe(Problem117 "117_blockPlaceMixProblem.cpp")
myexe(Problem118 "118_digitPrimeSet.cpp")
myexe(Problem119 "119_DigitPowerSum.cpp")
myexe(Problem120 "120_SquareRemainders.cpp")
myexe(Problem121 "121_DiscGamePrizeFund.cpp")
myexe(Problem122 "122_EfficientExponentiation.cpp")
myexe(Problem123 "123_PrimeSquareRemainders.cpp")
myexe(Problem124 "124_OrderedRadicals.cpp")
myexe(Problem125 "125_PalindromicSums.cpp")
myexe(Problem126 "126_CuboidLayers.cpp")
myexe(Problem127 "127_AbcHits.cpp")
myexe(Problem128 "128_HexagonalTileDifferences.cpp")
myexe(Problem129 "129_RepunitDivisibility.cpp")
myexe(Problem130 "130_CompositesWithPrimeRepunitProperty.cpp")
myexe(Test "Test.cpp")
