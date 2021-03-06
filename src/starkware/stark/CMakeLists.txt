add_library(committed_trace INTERFACE)
target_link_libraries(committed_trace INTERFACE cached_lde_manager table merkle_commitment_scheme packaging_commitment_scheme)

add_library(composition_oracle composition_oracle.cc)
target_link_libraries(composition_oracle committed_trace channel)

add_library(oods oods.cc)
target_link_libraries(oods breaker composition_oracle channel periodic_column)

add_library(stark stark.cc)
target_link_libraries(stark fri committed_trace composition_oracle oods channel json third_party profiling)

add_executable(committed_trace_test committed_trace_test.cc)
target_link_libraries(committed_trace_test committed_trace merkle_tree channel starkware_gtest)
add_test(committed_trace_test committed_trace_test)

# add_executable(composition_oracle_test composition_oracle_test.cc)
# target_link_libraries(composition_oracle_test composition_oracle starkware_gtest)
# add_test(composition_oracle_test composition_oracle_test)

add_executable(oods_test oods_test.cc)
target_link_libraries(oods_test oods test_air channel starkware_gtest)
add_test(oods_test oods_test)

add_executable(stark_test stark_test.cc)
target_link_libraries(stark_test stark test_air merkle_tree packaging_commitment_scheme proof_system starkware_gtest)
add_test(stark_test stark_test)
