import { createPublicClient, createWalletClient, http, parseAbi } from "viem"
import { arbitrumSepolia } from "viem/chains"
import { privateKeyToAccount } from "viem/accounts"
import "dotenv/config"

const ABI = parseAbi(["function hola_mundo() public view returns (string)"])

const account = privateKeyToAccount((process as any).env.PRIVATE_KEY)

const client = createWalletClient({
  chain: arbitrumSepolia,
  transport: http(),
  account,
})

const publicClient = createPublicClient({
  chain: arbitrumSepolia,
  transport: http(),
})

const CONTRACT_ADDRESS = "0x2df13fd774f887a7733ecb26c3e2791fbcaa898c"

async function read() {
  const result = await publicClient.readContract({
    abi: ABI,
    address: CONTRACT_ADDRESS,
    functionName: "hola_mundo",
  })

  console.debug(`Contract: ${result}`)
}
