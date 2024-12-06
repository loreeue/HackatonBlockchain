import { createPublicClient, http, parseAbi, stringToHex } from "viem"
import { arbitrumSepolia } from "viem/chains"
import "dotenv/config"

const ABI = parseAbi([
  "function hola_mundo() view returns (string)",
  "function calldata_len() view returns (uint256)",
  "function ping_pong(bytes32) view returns (string)",
])

const client = createPublicClient({
  chain: arbitrumSepolia,
  transport: http(),
})

// https://sepolia.arbiscan.io/address/0x6a5a8573fe27c42ce960dcb7a19cf957f0e8f837
const CONTRACT_ADDRESS = "0x6a5a8573fe27c42ce960dcb7a19cf957f0e8f837"

async function main() {
  const result = await client.readContract({
    abi: ABI,
    address: CONTRACT_ADDRESS,
    functionName: "ping_pong",
    args: [stringToHex("pong", { size: 32 })],
  })

  console.debug(`Contract: ${result}`)
}

main()
