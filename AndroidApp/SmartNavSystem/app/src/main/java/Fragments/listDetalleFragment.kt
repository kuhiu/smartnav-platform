package Fragments

import Entities.GlobalVar
import Entities.Objetos
import adapters.DetalleAdapter
import android.os.Bundle
import android.util.Log
import androidx.fragment.app.Fragment
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.preference.PreferenceManager
import androidx.recyclerview.widget.GridLayoutManager
import com.example.myapplication3.R
import com.google.android.material.snackbar.Snackbar
import com.google.firebase.storage.FirebaseStorage
import com.google.firebase.storage.StorageReference

class listDetalleFragment : Fragment() {

    lateinit var v: View

    private lateinit var recDetalle: RecyclerView
    private lateinit var linearLayoutManager: LinearLayoutManager

    lateinit var Objeto: Objetos

    // Instancio el adaptador
    private lateinit var MyAdaptadorDeDetalle: DetalleAdapter

    private lateinit var storage : FirebaseStorage
    private lateinit var gsRootRef : StorageReference
    private lateinit var gsReference : StorageReference


    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View {
        // Inflate the layout for this fragment
        v = inflater.inflate(R.layout.fragment_list_detalle, container, false)
        recDetalle = v.findViewById(R.id.rec_detalle)
        return v
    }

    override fun onStart() {
        super.onStart()
        Objeto = listDetalleFragmentArgs.fromBundle(requireArguments()).detalleObjeto
        //Objeto = Objetos("tomate", "gs://navsys-e2185.appspot.com/tomate/", R.drawable.tomate)
        storage = FirebaseStorage.getInstance()
        gsRootRef = storage.getReferenceFromUrl(Objeto.src)
        gsReference = storage.getReferenceFromUrl(Objeto.src+Objeto.nombre+".jpg")


        gsRootRef.listAll().addOnSuccessListener { arrayList ->
            GlobalVar.globalVar = arrayList.items.size
            GlobalVar.globalArray = arrayList.items
            MyAdaptadorDeDetalle.notifyDataSetChanged()
            //Log.d("Test", GlobalVar.globalVar.toString() + "onStart, adentro")
            //Log.d("Test", GlobalVar.globalArray.toString() + "onStart, adentro")
        }

        recDetalle.setHasFixedSize(true)                        // Acomoda el tamaño en la ventana

        val prefs = PreferenceManager.getDefaultSharedPreferences(requireContext())
        if( prefs.getString("layout_list_object","") == resources.getStringArray(R.array.layout_list_object)[1])
            linearLayoutManager = GridLayoutManager(context,2)
        else
            linearLayoutManager = LinearLayoutManager(context)

        recDetalle.layoutManager = linearLayoutManager

        MyAdaptadorDeDetalle = DetalleAdapter(v, storage, gsRootRef, gsReference, Objeto){
            onItemClick()
        }
        recDetalle.adapter = MyAdaptadorDeDetalle
        MyAdaptadorDeDetalle.notifyDataSetChanged()

    }

    private fun onItemClick () : Boolean {
        Snackbar.make(v,"Nombre del objeto: " + Objeto.nombre, Snackbar.LENGTH_SHORT).show()
        return true
    }

}


