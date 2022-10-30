package adapters

import Entities.Objetos
import Entities.GlobalVar
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import androidx.cardview.widget.CardView
import androidx.recyclerview.widget.RecyclerView
import com.bumptech.glide.Glide
import com.example.myapplication3.R
import com.google.firebase.storage.FirebaseStorage
import com.google.firebase.storage.StorageReference


class DetalleAdapter(private var v: View, private var storage: FirebaseStorage,
                     private var gsRootRef: StorageReference, private var gsReference: StorageReference,
                     private var Objeto: Objetos, val onItemClick: (Int) -> Boolean)
    : RecyclerView.Adapter<DetalleAdapter.DetalleHolder>()
{


    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): DetalleHolder {
        // Busco el item
        val view = LayoutInflater.from(parent.context).inflate(R.layout.detalle_item_objeto,parent,false)
        return(DetalleHolder(view))
    }

    override fun getItemCount() : Int {
        //Log.d("Test" , GlobalVar.globalVar.toString() + "get item count")
        return (GlobalVar.globalVar)
    }

    override fun onBindViewHolder(holder: DetalleHolder, position: Int) {
        //Log.d("Test" , "La posicion es: " + position.toString() )
        if ( GlobalVar.globalArray.size != 0 ){
            //Log.d("Test" , GlobalVar.globalArray.toString() + "onBindViewHolder"+gsReference.toString())
            //Log.d("Test" , GlobalVar.globalArray[position].toString() + "onBindViewHolder"+gsReference.toString())
            //Log.d("Test" , "La posicion es: " + position.toString() + " y el contenido " + GlobalVar.globalArray.toString() + " El total es " + GlobalVar.globalVar)
            Glide
                .with(v.context)
                .load(GlobalVar.globalArray[position])
                .centerInside()
                .into(holder.getImageView())

            holder.getCardLayout().setOnClickListener {
                onItemClick(position)
            }
        }

    }


    interface MyCallback{
        fun onCallback(value : Int): Int
    }

    //        readData( gsReference2, object : MyCallback {
    //            override fun onCallback(value: Int) : Int{
    //                Log.d("Test" , value.toString()+"trestiros")
    //                return value
    //            }
    //        })

    private fun readData (gsReference2 : StorageReference, MyCallback : MyCallback) {
        gsReference2.listAll().addOnSuccessListener { arrayList ->
            GlobalVar.globalVar = MyCallback.onCallback(arrayList.items.size)
            Log.d("Test", GlobalVar.globalVar.toString() + "readDatainside")
        }
        Log.d("Test" , GlobalVar.globalVar.toString() +"readDataOutside")
    }

    // Tiene las instancias del xml del item findviewid de los items
    // Todas las interacciones con el item van aca
    class DetalleHolder (v: View) : RecyclerView.ViewHolder(v) {
        private var view: View = v

//        fun setPic(src: Int) {
//            val pic: ImageView = view.findViewById(R.id.img_item_detalle)
//            pic.setImageResource(src)
//        }

        fun getCardLayout (): CardView {
            return view.findViewById(R.id.card_package_detalle)
        }

        fun getImageView () : ImageView {
            return view.findViewById(R.id.img_item_detalle)
        }
    }

}
