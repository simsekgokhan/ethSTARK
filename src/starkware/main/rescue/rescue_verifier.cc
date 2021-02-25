/*
  Verifies a Rescue hash chain proof. See rescue_prover_main.cc for more details.
*/

#include <memory>
#include <chrono>

#include "glog/logging.h"

#include "starkware/main/verifier_main_helper.h"
#include "starkware/statement/rescue/rescue_statement.h"
#include "starkware/utils/json.h"

bool rescue_verify(
    std::string const& proof_hex,
    std::string const& public_input,
    std::string const& parameters,
    std::string const& annotation_file_name
) {
  using namespace starkware;  // NOLINT

  try {
    RescueStatement statement(JsonValue::FromString(public_input), std::nullopt);

    ASSERT_RELEASE(!proof_hex.empty(), "Proof must not be empty.");
    std::vector<std::byte> proof((proof_hex.size()-1) / 2);
    starkware::HexStringToBytes(proof_hex, proof);  

    auto const start = std::chrono::system_clock::now();    
    
    bool result = starkware::VerifierMainHelper(
        &statement, 
        proof,      
        JsonValue::FromString(parameters),
        annotation_file_name
    );

    auto const end = std::chrono::system_clock::now();
    auto const time_elapsed = 
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "-------" << std::endl;
    std::cout << "--- time_elapsed: " << time_elapsed << " msec \n";
    std::cout << "-------" << std::endl;

    if (result) {
      LOG(INFO) << "Proof verified successfully.";
    } else {
      LOG(ERROR) << "Invalid proof.";
    }

    return result;
  } catch(std::exception const& e) {
    std::cout << "--- ethSTARK exception: " << e.what() << std::endl;
    return false;
  }
}
