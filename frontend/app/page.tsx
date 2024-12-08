"use client"

import { Tabs, TabsList, TabsContent, TabsTrigger } from "@/components/ui/tabs"
import { useRkAccountModal } from "@/lib/rainbowkit"
import { Fragment } from "react"
import { useAccount, useReadContract } from "wagmi"
import { parseAbi } from "viem"

import Navigation from "./Navigation"

// Definiendo la ABI del contrato
const ABI = parseAbi(["function hola_mundo() public view returns (string)"])

const ADDRESS = "0x2df13fd774f887a7733ecb26c3e2791fbcaa898c"

export default function Container() {
  /*const result = useReadContract({
    address: ADDRESS,
    functionName: "hola_mundo",
    abi: ABI,
  })*/

  const { openAccountModal } = useRkAccountModal()
  const { isConnected } = useAccount()

  return (
    <Fragment>
      {/* <p>{result.data || "Cargando..."}</p> */}
      <Navigation />
      <section className="max-w-5xl mt-12 mx-auto">
        {/* Sección para mostrar las portadas de los libros */}
        <div className="flex gap-4 overflow-x-auto">
          {[
            {
              id: 1,
              title: "Los 120 días de Sodoma",
              image: "https://m.media-amazon.com/images/I/81tCtHFkJnL._AC_UY327_FMwebp_QL65_.jpg"
            },
            {
              id: 2,
              title: "The Midnight Library",
              image: "https://m.media-amazon.com/images/I/81-QB7nDh4L._AC_UY327_FMwebp_QL65_.jpg"
            },
            {
              id: 3,
              title: "It Ends with Us",
              image: "https://m.media-amazon.com/images/I/71T0zw5dX5L._AC_UY327_FMwebp_QL65_.jpg"
            },
            {
              id: 4,
              title: "Lessons in Chemistry",
              image: "https://m.media-amazon.com/images/I/81vpj1ZFoGL._AC_UY327_FMwebp_QL65_.jpg"
            },
            {
              id: 5,
              title: "Project Hail Mary",
              image: "https://m.media-amazon.com/images/I/91qpRn3MF1L._AC_UY327_FMwebp_QL65_.jpg"
            }
          ].map((book) => (
            <div key={book.id} className="p-4 border rounded-lg flex flex-col items-center">
              <img src={book.image} alt={book.title} className="rounded-md mb-2" />
              <p className="text-center font-bold">{book.title}</p>
            </div>
          ))}
        </div>
      </section>
    </Fragment>
  );
}
