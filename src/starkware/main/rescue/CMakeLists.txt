# add_executable(rescue_prover rescue_prover_main.cc)
add_library(rescue_prover rescue_prover_main.cc)
target_link_libraries(rescue_prover rescue_air prover_main_helper flag_validators starkware_common rescue_statement)

# add_executable(rescue_verifier rescue_verifier_main.cc)
add_library(rescue_verifier rescue_verifier.cc) # using rescue_verifier.cc
target_link_libraries(rescue_verifier rescue_air verifier_main_helper flag_validators starkware_common rescue_statement)
