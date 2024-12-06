"use client"

import { Tabs, TabsList, TabsContent, TabsTrigger } from "@/components/ui/tabs"
import { useRkAccountModal } from "@/lib/rainbowkit"
import { useAccount } from "wagmi"

export default function Container() {
  const { openAccountModal } = useRkAccountModal()
  const { isConnected } = useAccount()

  return (
    <section className="max-w-2xl mt-12 mx-auto">
      <Tabs defaultValue="feed" className="w-full">
        <TabsList className="w-full p-0 border border-b-2 grid grid-cols-2">
          <TabsTrigger className="h-full" value="feed">
            Everything
          </TabsTrigger>
          <TabsTrigger
            onClick={() => {
              if (!isConnected) {
                // Abrimos el modal de conectar wallet
                // si no está conectado
                openAccountModal?.()
              }
            }}
            className="h-full"
            value="personal"
          >
            My publications
          </TabsTrigger>
        </TabsList>
        <TabsContent value="feed">
          <div className="grid grid-cols-3 gap-3">
            {Array.from({ length: 9 }).map((_, i) => (
              <section className="p-4 border rounded-lg">
                <nav className="flex items-center gap-1">
                  <strong>0x03242</strong>
                  <span className="opacity-70">posted</span>
                </nav>
                <p className="text-black/70 mt-2">
                  This is the feed where you can see all the posts from
                  everyone.
                </p>
              </section>
            ))}
          </div>
        </TabsContent>
        <TabsContent value="personal">My publications</TabsContent>
      </Tabs>
    </section>
  )
}
