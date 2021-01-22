/*
  Verifies a Rescue hash chain proof. See rescue_prover_main.cc for more details.
*/

#include <memory>

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

  RescueStatement statement(JsonValue::FromString(public_input), std::nullopt);

  ASSERT_RELEASE(!proof_hex.empty(), "Proof must not be empty.");
  std::vector<std::byte> proof((proof_hex.size()-1) / 2);
  starkware::HexStringToBytes(proof_hex, proof);  

  bool result = starkware::VerifierMainHelper(
      &statement, 
      proof,      
      JsonValue::FromString(parameters),
      annotation_file_name
  );

  if (result) {
    LOG(INFO) << "Proof verified successfully.";
  } else {
    LOG(ERROR) << "Invalid proof.";
  }

  return result;
}
