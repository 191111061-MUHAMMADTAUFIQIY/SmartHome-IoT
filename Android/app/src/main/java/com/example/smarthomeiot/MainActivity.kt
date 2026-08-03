package com.example.smarthomeiot

import android.os.Bundle
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import com.google.firebase.database.*

class MainActivity : AppCompatActivity() {

    lateinit var tvSuhu: TextView
    lateinit var tvKelembaban: TextView
    lateinit var tvPIR: TextView
    lateinit var tvLDR: TextView
    lateinit var tvLampu: TextView
    lateinit var tvKipas: TextView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        tvSuhu = findViewById(R.id.tvSuhu)
        tvKelembaban = findViewById(R.id.tvKelembaban)
        tvPIR = findViewById(R.id.tvPIR)
        tvLDR = findViewById(R.id.tvLDR)
        tvLampu = findViewById(R.id.tvLampu)
        tvKipas = findViewById(R.id.tvKipas)

        val database =
            FirebaseDatabase.getInstance().getReference("SmartHome")

        database.addValueEventListener(object : ValueEventListener {

            override fun onDataChange(snapshot: DataSnapshot) {

                val suhu =
                    snapshot.child("Suhu").getValue(Float::class.java)

                val kelembaban =
                    snapshot.child("Kelembaban").getValue(Float::class.java)

                val pir =
                    snapshot.child("PIR").getValue(String::class.java)

                val ldr =
                    snapshot.child("LDR").getValue(String::class.java)

                val lampu =
                    snapshot.child("Lampu").getValue(String::class.java)

                val kipas =
                    snapshot.child("Kipas").getValue(String::class.java)

                tvSuhu.text = "${suhu ?: 0} °C"
                tvKelembaban.text = "${kelembaban ?: 0} %"

                tvPIR.text = pir ?: "-"
                tvLDR.text = ldr ?: "-"
                tvLampu.text = lampu ?: "-"
                tvKipas.text = kipas ?: "-"
            }

            override fun onCancelled(error: DatabaseError) {

            }
        })
    }
}